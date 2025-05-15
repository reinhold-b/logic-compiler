%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "syntaxtree.h"
#include "generate.h"
#include "optimize.h"


extern FILE *yyin;
// Declare the lexer function
int yylex();
void yyerror(const char *s);

static int quantorCounter = 0;
static int argumentCounter = 0;

// Assuming mkBinaryNode is declared in syntaxtree.h
// Node* mkBinaryNode(Node* left, Node* right, const char* operator);
// Assuming mkUnaryNode, mkQuantorNode, mkPredicateNode, mkFunctionNode,
// mkVariableNode, mkNumberNode, mkTrueNode, mkFalseNode, mkArgNode, mkFcArgNode
// and countArgumentsOfNode are declared in syntaxtree.h
// Assuming freeSyntaxTree is declared in syntaxtree.h
// Assuming clearSymbolTable() is declared in symboltable.h and implemented in symboltable.c

%}

%union {
	char p[101];
	int num;
	struct Node* n;
	struct SyntaxTree* t;
	struct Node* arg;
}

/* Define token types */
%token DECLARE PREDICATE FUNCTION VARIABLE EXIST ALL TTRUE TFALSE
%token SQUARE_OPEN SQUARE_CLOSE BRACKET_OPEN BRACKET_CLOSE
%token COLON COMMA TILDE SEMICOLON

/* Operator precedence and associativity */
/* TILDE (negation) has highest precedence implicitly as it's not listed here */
%left IMPLIES
%left EQUALS
%left OR
%left AND


%token <p> STRING	/* Predicate name */
%token <num> NUMBER
%type <t> program_list program
%type <n> top_level_formula logical_expression equivalence_expression implication_expression or_expression and_expression negated_expression primary_expression predicate_call quantifier function_call true false boolean
%type <arg> predicate_params

%start program_list // Set program_list as the start symbol

%%

// Top-level rule to parse a list of programs
program_list:
	program
	| program_list program
	;

// Rule for a single program (declarations + formula + semicolon)
program:
	declarations top_level_formula SEMICOLON {
		SyntaxTree* tree = malloc(sizeof(SyntaxTree));
		if ($2 == NULL) {
			fprintf(stderr, "PAR: No top-level formula found for this program.\n");
			tree->root = NULL;
		} else {
			fprintf(stderr, "PAR: Top-level formula found for this program.\n");
			tree->root = $2;	// $2 is the root of the formula tree for this program

			fprintf(stderr, "Initial Parse Tree for Program:\n");
			printTree(tree->root, 0);

			fprintf(stderr, "Starting optimization for Program...\n");

			// Apply optimization passes for this single program's tree
			for (int i = 0; i < 5; i++) { // Increased passes for thoroughness
				tree->root = removeImplicationsAndEquivalences(tree->root);
				printTree(tree->root, 0);
				tree->root = pushNegationsToPredicates(tree->root);
				printTree(tree->root, 0);
				tree->root = removeDoubleNeg(tree->root); // Apply multiple times as negations are pushed
				printTree(tree->root, 0);
				tree->root = evaluateBooleanOperators(tree->root); // Apply multiple times for cascading effects
				// If needed, add toPrenexForm here or after the loop
				// tree->root = toPrenexForm(tree->root);
			}

			fprintf(stderr, "Optimized Tree for Program:\n");
			printTree(tree->root, 0);
			fprintf(stderr, "Starting code generation for Program.\n");
			generateCode(tree->root);

            // Optional: Free the syntax tree for this program if not needed later
            // freeSyntaxTree(tree->root); // Uncomment if you have this function and want to free memory per program
		}
        // Free the SyntaxTree structure itself, but not the nodes if freeSyntaxTree is not used
        // free(tree); // Uncomment if you want to free the tree structure per program

        // Clear the symbol table AFTER processing the program
        // You need to implement clearSymbolTable() in symboltable.c/h
        clearSymbolTable();
        // Reset counters for unique IDs if they should be per-program
        quantorCounter = 0;
        argumentCounter = 0;

        // This rule doesn't return a Node* or SyntaxTree*, it just performs actions.
        // $$ = NULL; // Or some indicator if needed, but usually actions suffice for list elements.
	}
	;

declarations:
	/* Empty */
	| declarations pred_dec
	| declarations var_dec
	| declarations func_dec
	;

// Rule for the main formula of a single program
// This now allows the highest precedence operator (EQUALS) at the top level
top_level_formula:
	logical_expression // A single program's formula is a logical_expression
	;


pred_dec:
	DECLARE PREDICATE STRING COLON NUMBER {
		printf("PAR: Predicate Declaration: %s (Arity: %d)\n", $3, $5);
		addSymEntry($3, $3, Predicate, $5);
	}
	;

var_dec:
	DECLARE VARIABLE STRING COLON STRING { // Assuming variable type is given as string like "int"
		printf("PAR: Variable Declaration: %s : %s\n", $3, $5);
		// Assuming arity 0 for variables
		addSymEntry($3, $3, Var, 0); // Store type string if needed, arity is 0 for simple vars
	}
	;

func_dec:
	DECLARE FUNCTION STRING COLON NUMBER { // Number represents arity
		printf("PAR: Function Declaration: %s (Arity: %d)\n", $3, $5);
		addSymEntry($3, $3, Function, $5);
	}
	;

true:
	TTRUE {
		fprintf(stderr, "PAR: TRUE\n");
		$$ = mkTrueNode();
	};

false:
	TFALSE {
		fprintf(stderr, "PAR: FALSE\n"); // Corrected log message
		$$ = mkFalseNode();
	};

boolean:
	true |
	false ;

quantifier:
	EXIST SQUARE_OPEN STRING SQUARE_CLOSE logical_expression { // Changed back to logical_expression
		printf("PAR: EXIST[%s]\n", $3);
		char uniqueId[128];
		// Create a unique identifier for the quantified variable in this scope
		snprintf(uniqueId, sizeof(uniqueId), "%s_%d_q", $3, quantorCounter++);
		// Add the quantified variable to the symbol table with its unique ID but original public name
		addSymEntry(uniqueId, $3, Q_exists, 0); // Arity 0 for quantified variables
		SymTableEntry* entry = getSymEntry(uniqueId);
		if (!entry) {
			fprintf(stderr, "PAR: Error finding symbol table entry for quantified variable %s\n", uniqueId);
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "PAR: %s QUANTIFIER (%s)\n", typeToString(entry->type), entry->identifier);
		$$ = mkQuantorNode(entry, $5);
	}
	| ALL SQUARE_OPEN STRING SQUARE_CLOSE logical_expression { // Changed back to logical_expression
		printf("PAR: ALL[%s]\n", $3);
		char uniqueId[128];
		// Create a unique identifier for the quantified variable in this scope
		snprintf(uniqueId, sizeof(uniqueId), "%s_%d_q", $3, quantorCounter++);
		// Add the quantified variable to the symbol table with its unique ID but original public name
		addSymEntry(uniqueId, $3, Q_all, 0); // Arity 0 for quantified variables
		SymTableEntry* entry = getSymEntry(uniqueId);
		if (!entry) {
			fprintf(stderr, "PAR: Error finding symbol table entry for quantified variable %s\n", uniqueId);
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "PAR: %s QUANTIFIER (%s)\n", typeToString(entry->type), entry->identifier);
		$$ = mkQuantorNode(entry, $5);
	}
	;

predicate_call:
	STRING BRACKET_OPEN predicate_params BRACKET_CLOSE {
		printf("PAR: Predicate Call: %s\n", $1);
		SymTableEntry* entry = getSymEntry($1);
		if (!entry || entry->type != Predicate) { // Check if it's declared as a predicate
			fprintf(stderr, "PAR: Error: '%s' is not declared as a predicate.\n", $1);
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "SYT: New pred node: %p\n", $3); // Pass the Node* directly
		$$ = mkPredicateNode(entry, $3);

		int givenArgs = countArgumentsOfNode($$);
		if (givenArgs != entry->arity) {
			fprintf(stderr, "AST: ARITY ERROR: Predicate '%s' (expected %d arguments, got %d)\n", entry->identifier, entry->arity, givenArgs);
			exit(EXIT_FAILURE);
		}
	}
	;

predicate_params:
	/* empty */ {
		$$ = NULL;
	}
	| true {
		// Original logic: create a SymTableEntry for the literal and use mkArgNode
		char uniqueId[128];
		snprintf(uniqueId, sizeof(uniqueId), "TRUE_%d", argumentCounter++);
		addSymEntry(uniqueId, "TRUE", Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %s\n", uniqueId);
		$$ = mkArgNode(entry, NULL);
		fprintf(stderr, "PAR: Arg: TRUE\n");
	}
	| false {
		// Original logic: create a SymTableEntry for the literal and use mkArgNode
		char uniqueId[128];
		snprintf(uniqueId, sizeof(uniqueId), "FALSE_%d", argumentCounter++);
		addSymEntry(uniqueId, "FALSE", Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %s\n", uniqueId);
		$$ = mkArgNode(entry, NULL);
		fprintf(stderr, "PAR: Arg: FALSE\n");
	}
	| NUMBER {
		// Original logic: create a SymTableEntry for the number and use mkArgNode
		char uniqueId[128];
		char temp[30];
		sprintf(temp, "%d", $1);
		snprintf(uniqueId, sizeof(uniqueId), "%d_%d", $1, argumentCounter++);
		addSymEntry(uniqueId, temp, Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %d\n", $1);
		$$ = mkArgNode(entry, NULL); // Only one argument, no next
		fprintf(stderr, "PAR: Arg: %d\n", $1);
	}
	| STRING { // This should be a variable or a constant like "Tim"
		// Original logic: get SymTableEntry for the string and use mkArgNode
		SymTableEntry* entry = getSymEntry($1);
		// Note: Your original code checked for entry->type != Var here,
		// but based on your comment "i didnt use any var in my previous parser, i save strings as identifiers, eg Tim"
		// and the need to handle constants like "Tim", we assume STRINGs here
		// are looked up in the symbol table and used as arguments via mkArgNode.
		// If "Tim" is declared as a VARIABLE, this will work. If it's just a string literal
		// not in the symbol table, getSymEntry will return NULL, which needs handling.
		if (!entry) {
			// If string is not in symbol table, treat it as a new argument identifier
			char uniqueId[128];
			snprintf(uniqueId, sizeof(uniqueId), "%s_%d", $1, argumentCounter++);
			addSymEntry(uniqueId, $1, Argument, 0); // Assuming Argument type exists
			entry = getSymEntry(uniqueId); // Retrieve the newly added entry
			fprintf(stderr, "SYT: New symtable entry for string literal: %s\n", uniqueId);
		} else {
			// If string is found, use the existing entry
			fprintf(stderr, "SYT: Found existing symtable entry for string: %s\n", entry->identifier);
		}
		$$ = mkArgNode(entry, NULL);
		fprintf(stderr, "PAR: Arg: String '%s'\n", $1);
	}
	| function_call {
		fprintf(stderr, "PAR: Arg: Function Call '%s'\n", $1->types.functionType.symEntry->identifier);
		// Original logic: Using mkFcArgNode for function calls as arguments
		$$ = mkFcArgNode($1, NULL);	// function node as value, no next arg
	}
	| predicate_params COMMA true {
		// Original logic: create a SymTableEntry for the literal and use mkArgNode in a list
		char uniqueId[128];
		snprintf(uniqueId, sizeof(uniqueId), "TRUE_%d", argumentCounter++);
		addSymEntry(uniqueId, "TRUE", Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %s\n", uniqueId);
		$$ = mkArgNode(entry, $1); // New arg goes before $1
		fprintf(stderr, "PAR: Arg: TRUE (followed by previous args)\n");
	}
	| predicate_params COMMA false {
		// Original logic: create a SymTableEntry for the literal and use mkArgNode in a list
		char uniqueId[128];
		snprintf(uniqueId, sizeof(uniqueId), "FALSE_%d", argumentCounter++);
		addSymEntry(uniqueId, "FALSE", Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %s\n", uniqueId);
		$$ = mkArgNode(entry, $1); // New arg goes before $1
		fprintf(stderr, "PAR: Arg: FALSE (followed by previous args)\n");
	}
	| predicate_params COMMA NUMBER {
		// Original logic: create a SymTableEntry for the number and use mkArgNode in a list
		char uniqueId[128];
		char temp[30];
		sprintf(temp, "%d", $3);
		snprintf(uniqueId, sizeof(uniqueId), "%d_%d", $3, argumentCounter++);
		addSymEntry(uniqueId, temp, Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %d\n", $3);
		$$ = mkArgNode(entry, $1); // New arg goes before $1
		fprintf(stderr, "PAR: Arg: %d (followed by previous args)\n");
	}
	| predicate_params COMMA STRING { // This should be a variable or a constant like "Tim"
		// Original logic: get SymTableEntry for the string and use mkArgNode in a list
		SymTableEntry* entry = getSymEntry($3);
		if (!entry) {
			// If string is not in symbol table, treat it as a new argument identifier
			char uniqueId[128];
			snprintf(uniqueId, sizeof(uniqueId), "%s_%d", $3, argumentCounter++);
			addSymEntry(uniqueId, $3, Argument, 0); // Assuming Argument type exists
			entry = getSymEntry(uniqueId); // Retrieve the newly added entry
			fprintf(stderr, "SYT: New symtable entry for string literal: %s\n", uniqueId);
		} else {
			// If string is found, use the existing entry
			fprintf(stderr, "SYT: Found existing symtable entry for string: %s\n", entry->identifier);
		}
		$$ = mkArgNode(entry, $1); // Build linked list with $1 as next
		fprintf(stderr, "PAR: Arg: String '%s' (followed by previous args)\n");
	}
	| predicate_params COMMA function_call {
		fprintf(stderr, "PAR: Arg: Function Call '%s' (followed by previous args)\n", $3->types.functionType.symEntry->identifier);
		// Original logic: Using mkFcArgNode for function calls as arguments in a list
		$$ = mkFcArgNode($3, $1); // new arg goes before $1
	}
	;

function_call:
	STRING BRACKET_OPEN predicate_params BRACKET_CLOSE {
		printf("PAR: Function Call: %s\n", $1);
		SymTableEntry* entry = getSymEntry($1);
		if (!entry || entry->type != Function) { // Check if it's declared as a function
			fprintf(stderr, "PAR: Error: '%s' is not declared as a function.\n", $1);
			exit(EXIT_FAILURE);
		}

		fprintf(stderr, "AST: Building function node for '%s'\n", $1);
		$$ = mkFunctionNode(entry, $3);

		// Optional: Check arity for functions
		int givenArgs = countArgumentsOfNode($$); // You might need a similar function for function nodes
		if (givenArgs != entry->arity) {
			fprintf(stderr, "AST: ARITY ERROR: Function '%s' (expected %d arguments, got %d)\n", entry->identifier, entry->arity, givenArgs);
			exit(EXIT_FAILURE);
		}
	}
	;

/* Refactored logical_expression rules for correct precedence */

logical_expression: equivalence_expression ;

equivalence_expression: implication_expression
					  | equivalence_expression EQUALS implication_expression { $$ = mkBinaryNode($1, $3, "EQUALS"); }
					  ;

implication_expression: or_expression
					  | implication_expression IMPLIES or_expression { $$ = mkBinaryNode($1, $3, "IMPLIES"); }
					  ;

or_expression: and_expression
			 | or_expression OR and_expression { $$ = mkBinaryNode($1, $3, "OR"); }
			 ;

and_expression: negated_expression
			  | and_expression AND negated_expression { $$ = mkBinaryNode($1, $3, "AND"); }
			  ;

negated_expression: primary_expression
					| TILDE negated_expression { $$ = mkUnaryNode($2); } // Allows ~~A and negation of complex expressions
					;

primary_expression: predicate_call
					| quantifier
					| BRACKET_OPEN logical_expression BRACKET_CLOSE { $$ = $2; } // Parentheses force evaluation of inner expression
					| boolean
					;

%%

/* Error handling function */
void yyerror(const char *s) {
	fprintf(stderr, "PAR: Error: %s\n", s);
}

/* Main function */
int main(int argc, char **argv) {
	++argv, --argc;	/* skip over program name */

	if (argc > 0) {
		yyin = fopen(argv[0], "r");
		if (!yyin) {
			perror("Fehler beim Öffnen der Eingabedatei");
			return 1;
		}
	} else {
		yyin = stdin;
	}

    // *** NEU: Datei einmalig im Schreibmodus öffnen und Header schreiben ***
    FILE *output_file = fopen("output.pl1", "w");
    if (output_file == NULL) {
        perror("Fehler beim Öffnen der Ausgabedatei für Header");
        if (yyin != stdin) fclose(yyin);
        return 1;
    }
    fprintf(output_file, "/* CREATED BY PL1C */\n\n");
    fclose(output_file);
    // *** Ende NEU ***


	int result = yyparse();
	fprintf(stderr, "Parsing result: %d\n", result); // Log the result of yyparse

	if (yyin != stdin) fclose(yyin);	// Close file if not stdin

	return 0;
}

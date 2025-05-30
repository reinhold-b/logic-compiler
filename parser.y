%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "syntaxtree.h"
#include "generate.h"
#include "optimize.h"


extern FILE *yyin;
int yylex();
void yyerror(const char *s);

static int quantorCounter = 0;
static int argumentCounter = 0;
%}

%union {
	char p[101];
	int num;
	struct Node* n;
	struct SyntaxTree* t;
	struct Node* arg_head;
	struct Node* arg_item;
}

%token DECLARE PREDICATE FUNCTION VARIABLE EXIST ALL TTRUE TFALSE
%token SQUARE_OPEN SQUARE_CLOSE BRACKET_OPEN BRACKET_CLOSE
%token COLON COMMA TILDE SEMICOLON

%left IMPLIES
%left EQUALS
%left OR
%left AND
%right TILDE

%token <p> STRING
%token <num> NUMBER
%type <t> program_list program
%type <n> top_level_formula logical_expression equivalence_expression implication_expression or_expression and_expression negated_expression primary_expression predicate_call quantifier function_call true false boolean
%type <arg_head> predicate_params
%type <arg_item> argument_item

%start program_list

%%

program_list:
	program
	| program_list program
	;

program:
	declarations top_level_formula SEMICOLON {
		SyntaxTree* tree = malloc(sizeof(SyntaxTree));
		if ($2 == NULL) {
			fprintf(stderr, "PAR: No top-level formula found for this program.\n");
			tree->root = NULL;
		} else {
			fprintf(stderr, "PAR: Top-level formula found for this program.\n");
			tree->root = $2;

			fprintf(stderr, "Initial Parse Tree for Program:\n");
			printTree(tree->root, 0);

			fprintf(stderr, "Starting optimization for Program...\n");

			for (int i = 0; i < 5; i++) {
				Node* prev_root = tree->root;

				tree->root = removeImplicationsAndEquivalences(tree->root);
				if (tree->root != prev_root) { fprintf(stderr, "After removeImplicationsAndEquivalences:\n"); printTree(tree->root, 0); prev_root = tree->root; }

				tree->root = pushNegationsToPredicates(tree->root);
				if (tree->root != prev_root) { fprintf(stderr, "After pushNegationsToPredicates:\n"); printTree(tree->root, 0); prev_root = tree->root; }

				tree->root = removeDoubleNeg(tree->root);
				if (tree->root != prev_root) { fprintf(stderr, "After removeDoubleNeg:\n"); printTree(tree->root, 0); prev_root = tree->root; }

				tree->root = evaluateBooleanOperators(tree->root);
				if (tree->root != prev_root) { 
					fprintf(stderr, "After evaluateBooleanOperators:\n"); printTree(tree->root, 0); prev_root = tree->root; 
				}
			}

			fprintf(stderr, "Optimized Tree for Program:\n");
			printTree(tree->root, 0);
			fprintf(stderr, "Starting code generation for Program.\n");
			generateCode(tree->root);

		}
		clearSymbolTable();
		quantorCounter = 0;
		argumentCounter = 0;

		free(tree);
		fprintf(stderr, "Finished.\n\n");
	}
	;

declarations:
	| declarations pred_dec
	| declarations var_dec
	| declarations func_dec
	;

top_level_formula:
	logical_expression
	;


pred_dec:
	DECLARE PREDICATE STRING COLON NUMBER {
		printf("PAR: Predicate Declaration: %s (Arity: %d)\n", $3, $5);
		addSymEntry($3, $3, Predicate, $5);
	}
	;

var_dec:
	DECLARE VARIABLE STRING COLON STRING {
		printf("PAR: Variable Declaration: %s : %s\n", $3, $5);
		addSymEntry($3, $3, Var, 0);
	}
	;

func_dec:
	DECLARE FUNCTION STRING COLON NUMBER {
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
		fprintf(stderr, "PAR: FALSE\n");
		$$ = mkFalseNode();
	};

boolean:
	true |
	false ;

quantifier:
	EXIST SQUARE_OPEN STRING SQUARE_CLOSE negated_expression {
		printf("PAR: EXIST[%s]\n", $3);
		char uniqueId[128];
		snprintf(uniqueId, sizeof(uniqueId), "%s_%d_q", $3, quantorCounter++);
		addSymEntry(uniqueId, $3, Q_exists, 0);
		SymTableEntry* entry = getSymEntry(uniqueId);
		if (!entry) {
			fprintf(stderr, "PAR: Error finding symbol table entry for quantified variable %s\n", uniqueId);
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "PAR: %s QUANTIFIER (%s)\n", typeToString(entry->type), entry->identifier);
		$$ = mkQuantorNode(entry, $5);
	}
	| ALL SQUARE_OPEN STRING SQUARE_CLOSE negated_expression {
		printf("PAR: ALL[%s]\n", $3);
		char uniqueId[128];
		snprintf(uniqueId, sizeof(uniqueId), "%s_%d_q", $3, quantorCounter++);
		addSymEntry(uniqueId, $3, Q_all, 0);
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
		if (!entry || entry->type != Predicate) {
			fprintf(stderr, "PAR: Error: '%s' is not declared as a predicate.\n", $1);
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "SYT: New pred node with args starting at %p\n", $3);
		$$ = mkPredicateNode(entry, $3);

		int givenArgs = countArgumentsOfNode($$);
		if (givenArgs != entry->arity) {
			fprintf(stderr, "AST: ARITY ERROR: Predicate '%s' (expected %d arguments, got %d)\n", entry->identifier, entry->arity, givenArgs);
			exit(EXIT_FAILURE);
		}
	}
	;

argument_item:
    TTRUE {
        char uniqueId[128]; snprintf(uniqueId, sizeof(uniqueId), "TRUE_%d", argumentCounter++);
        addSymEntry(uniqueId, "TRUE", Argument, 0); SymTableEntry* entry = getSymEntry(uniqueId);
        $$ = mkArgNode(entry, NULL);
        fprintf(stderr, "PAR: Arg Item: TRUE\n");
    }
    | TFALSE {
        char uniqueId[128]; snprintf(uniqueId, sizeof(uniqueId), "FALSE_%d", argumentCounter++);
        addSymEntry(uniqueId, "FALSE", Argument, 0); SymTableEntry* entry = getSymEntry(uniqueId);
        $$ = mkArgNode(entry, NULL);
        fprintf(stderr, "PAR: Arg Item: FALSE\n");
    }
    | NUMBER {
        char uniqueId[128]; char temp[30]; sprintf(temp, "%d", $1); snprintf(uniqueId, sizeof(uniqueId), "NUM_%d_%d", $1, argumentCounter++);
        addSymEntry(uniqueId, temp, Argument, 0); SymTableEntry* entry = getSymEntry(uniqueId);
        $$ = mkArgNode(entry, NULL);
        fprintf(stderr, "PAR: Arg Item: %d\n", $1);
    }
    | STRING {
        SymTableEntry* entry = getSymEntry($1);
        if (!entry) {
            char uniqueId[128]; snprintf(uniqueId, sizeof(uniqueId), "%s_ARG_%d", $1, argumentCounter++);
            addSymEntry(uniqueId, $1, Argument, 0); entry = getSymEntry(uniqueId);
        }
        $$ = mkArgNode(entry, NULL);
        fprintf(stderr, "PAR: Arg Item: String '%s'\n", $1);
    }
    | function_call {
        fprintf(stderr, "PAR: Arg Item: Function Call '%s'\n", $1->types.functionType.symEntry->identifier);
        $$ = mkFcArgNode($1, NULL);
    }
    ;

predicate_params:
   { $$ = NULL; }
    | argument_item { $$ = $1; }
    | predicate_params COMMA argument_item {
        Node* head = $1;
        Node* new_arg = $3;
        if (head == NULL) {
            $$ = new_arg;
        } else {
            Node* current = head;
            while (1) {
                if (current->nodeType == NODE_SIMPLE_ARGUMENT) {
                    if (current->types.simpleArgumentType.nextArg == NULL) break;
                    current = current->types.simpleArgumentType.nextArg;
                } else if (current->nodeType == NODE_FUNCTION_ARGUMENT) {
                    if (current->types.functionArgumentType.nextArg == NULL) break;
                    current = current->types.functionArgumentType.nextArg;
                } else {
                    fprintf(stderr, "PARSER ERROR: Unexpected node type (%d) in argument list traversal in predicate_params. List corrupted.\n", current->nodeType);
                    break;
                }
            }
            if (current->nodeType == NODE_SIMPLE_ARGUMENT) {
                current->types.simpleArgumentType.nextArg = new_arg;
            } else if (current->nodeType == NODE_FUNCTION_ARGUMENT) {
                current->types.functionArgumentType.nextArg = new_arg;
            } else {
                fprintf(stderr, "PARSER ERROR: Cannot append to unexpected node type (%d) in predicate_params. List corrupted.\n", current->nodeType);
            }
            $$ = head;
        }
    }
    ;

function_call:
	STRING BRACKET_OPEN predicate_params BRACKET_CLOSE {
		printf("PAR: Function Call: %s\n", $1);
		SymTableEntry* entry = getSymEntry($1);
		if (!entry || entry->type != Function) {
			fprintf(stderr, "PAR: Error: '%s' is not declared as a function.\n", $1);
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "AST: Building function node for '%s' with args starting at %p\n", $1, $3);
		$$ = mkFunctionNode(entry, $3);

		int givenArgs = countArgumentsOfNode($$);
		if (givenArgs != entry->arity) {
			fprintf(stderr, "AST: ARITY ERROR: Function '%s' (expected %d arguments, got %d)\n", entry->identifier, entry->arity, givenArgs);
			exit(EXIT_FAILURE);
		}
	}
	;


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
					| TILDE negated_expression { $$ = mkUnaryNode($2); }
					;

primary_expression: predicate_call
					| quantifier
					| BRACKET_OPEN logical_expression BRACKET_CLOSE { $$ = $2; }
					| boolean
					;

%%

void yyerror(const char *s) {
	fprintf(stderr, "PAR: Error: %s\n", s);
}

int main(int argc, char **argv) {
	++argv, --argc;

	if (argc > 0) {
		yyin = fopen(argv[0], "r");
		if (!yyin) {
			perror("Fehler beim Öffnen der Eingabedatei");
			return 1;
		}
	} else {
		yyin = stdin;
	}

	FILE *output_file = fopen("output.pl1", "w");
	if (output_file == NULL) {
		perror("Fehler beim Öffnen der Ausgabedatei für Header");
		if (yyin != stdin) fclose(yyin);
		return 1;
	}
	fprintf(output_file, "/* CREATED BY PL1C */\n\n");
	fclose(output_file);

	int result = yyparse();
	fprintf(stderr, "Parsing result: %d\n", result);

	if (yyin != stdin) fclose(yyin);

	return 0;
}
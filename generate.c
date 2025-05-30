#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symboltable.h"
#include "syntaxtree.h"

const char* typeToString(SymTableType type) {
    switch (type) {
        case Predicate: return "Predicate";
        case Function: return "Function";
        case Var: return "Variable";
        case Q_all: return "ALL";
        case Q_exists: return "EXIST";
        case Argument: return "Argument";
        default: return "Unknown";
    }
}

const char* operatorToSymbol(char* operatorString) {
    if (strcmp(operatorString, "AND") == 0) return "&";
    else if (strcmp(operatorString, "OR") == 0) return "|";
    else if (strcmp(operatorString, "IMPLIES") == 0) return "->";
    else if (strcmp(operatorString, "EQUALS") == 0) return "<->";
    return "";
}

void printNode(Node* node, FILE* file, int recursionLevel);

void printArgs(Node* arg_head, FILE* file, int recursionLevel) {
    Node* currentArg = arg_head;
    int first = 1;

    while (currentArg != NULL) {
        if (!first) {
            fprintf(file, ", ");
        }
        first = 0;

        if (currentArg->nodeType == NODE_SIMPLE_ARGUMENT) {
            if (currentArg->types.simpleArgumentType.symEntry) {
                fprintf(file, "%s", currentArg->types.simpleArgumentType.symEntry->publicName);
            } else {
                fprintf(file, "<null_simple_arg>");
            }
            currentArg = currentArg->types.simpleArgumentType.nextArg;
        } else if (currentArg->nodeType == NODE_FUNCTION_ARGUMENT) {
            if (currentArg->types.functionArgumentType.functionCallNode) {
                printNode(currentArg->types.functionArgumentType.functionCallNode, file, recursionLevel);
            } else {
                fprintf(file, "<null_func_arg_node>");
            }
            currentArg = currentArg->types.functionArgumentType.nextArg;
        } else {
            fprintf(file, "<invalid_arg_node_type:%d>", currentArg->nodeType);
            fprintf(stderr, "ERROR: printArgs encountered unexpected node type %d in argument list.\n", currentArg->nodeType);
            break;
        }
    }
}

void printNode(Node* node, FILE* file, int recursionLevel) {
    if (!node) {
        fprintf(stderr, "DEBUG[%d]: NULL node encountered during printNode call.\n", recursionLevel);
        return;
    }

    fprintf(stderr, "DEBUG[%d]: Visiting node of type %d (ID: %s)\n", recursionLevel, node->nodeType,
            (node->nodeType == NODE_PREDICATE || node->nodeType == NODE_FUNCTION || node->nodeType == NODE_QUANTOR || node->nodeType == NODE_VARIABLE) && node->types.functionType.symEntry ? node->types.functionType.symEntry->identifier : "N/A");

    switch (node->nodeType) {
        case NODE_UNARY: {
            fprintf(file, "~");
            fprintf(file, "(");
            printNode(node->types.unaryType.child, file, recursionLevel + 1);
            fprintf(file, ")");
            break;
        }

        case NODE_BINARY: {
            fprintf(file, "(");
            printNode(node->types.binaryType.left, file, recursionLevel + 1);
            fprintf(file, " %s ", operatorToSymbol(node->types.binaryType.operator));
            
            if (strcmp(node->types.binaryType.operator, "AND") == 0) {
                fprintf(file, "\n");
                for (int i = 0; i < (recursionLevel + 1) * 2; i++) {
                    fprintf(file, " ");
                }
            }

            printNode(node->types.binaryType.right, file, recursionLevel + 1);
            fprintf(file, ")");
            break;
        }

        case NODE_PREDICATE: {
            SymTableEntry* entry = node->types.predicateType.symEntry;
            if (entry) {
                fprintf(file, "%s(", entry->identifier);
                printArgs(node->types.predicateType.arg, file, recursionLevel + 1);
                fprintf(file, ")");
            } else {
                fprintf(stderr, "ERROR[%d]: Predicate node has null symEntry.\n", recursionLevel);
                fprintf(file, "<null_predicate_name>()");
            }
            break;
        }

        case NODE_FUNCTION: {
            SymTableEntry* entry = node->types.functionType.symEntry;
            if (entry) {
                fprintf(file, "%s(", entry->identifier);
                printArgs(node->types.functionType.arg, file, recursionLevel + 1);
                fprintf(file, ")");
            } else {
                fprintf(stderr, "ERROR[%d]: Function node has null symEntry.\n", recursionLevel);
                fprintf(file, "<null_function_name>()");
            }
            break;
        }

        case NODE_QUANTOR: {
            SymTableEntry* entry = node->types.quantorType.entry;
            if (entry) {
                fprintf(file, "%s[%s](", typeToString(entry->type), entry->publicName);
                if (node->types.quantorType.child) {
                    printNode(node->types.quantorType.child, file, recursionLevel + 1);
                } else {
                    fprintf(stderr, "ERROR[%d]: Quantor node has no child expression.\n", recursionLevel);
                    fprintf(file, "<null_quantor_body>");
                }
                fprintf(file, ")");
            } else {
                fprintf(stderr, "ERROR[%d]: Quantor node has null entry.\n", recursionLevel);
                fprintf(file, "<null_quantor_var>()");
            }
            break;
        }

        case NODE_VARIABLE: {
            SymTableEntry* entry = node->types.variableType.symEntry;
            if (entry) {
                fprintf(file, "%s", entry->publicName);
            } else {
                fprintf(stderr, "ERROR[%d]: Variable node has null symEntry.\n", recursionLevel);
                fprintf(file, "<null_variable>");
            }
            break;
        }

        case NODE_NUMBER: {
            fprintf(file, "%d", node->types.numberType.value);
            break;
        }

        case NODE_TRUE:
            fprintf(file, "TRUE");
            break;

        case NODE_FALSE:
            fprintf(file, "FALSE");
            break;

        case NODE_SIMPLE_ARGUMENT:
        case NODE_FUNCTION_ARGUMENT:
            fprintf(stderr, "ERROR[%d]: printNode called directly on an ARGUMENT node type (%d). This indicates a structural AST error.\n", recursionLevel, node->nodeType);
            fprintf(file, "<AST_ERROR_ARG_NODE>");
            break;

        default: {
            fprintf(stderr, "ERROR[%d]: Unknown node type %d encountered during printNode.\n", recursionLevel, node->nodeType);
            fprintf(file, "<UNKNOWN_NODE_TYPE>");
            break;
        }
    }
}

void printDeclarations(FILE* file) {
    SymTable symTable = table;
    fprintf(file, "\n\n");

    for (int i = 0; i < tableAdr; i++) {
        SymTableEntry* entry = &symTable.entries[i];
        
        fprintf(stderr, "DEBUG: Declaring '%s' (Type: %s, Arity: %d)\n",
                entry->identifier, typeToString(entry->type), entry->arity);

        if (entry->type == Predicate || entry->type == Function || entry->type == Var) {
            fprintf(file, "DECLARE %s %s", typeToString(entry->type), entry->identifier);
            if (entry->type == Var) {
                fprintf(file, " : int");
            } else {
                fprintf(file, " : %d", entry->arity);
            }
            fprintf(file, ";\n");
        }
    }
    fprintf(file, "\n\n");
}

void generateCode(Node* tree) {
    FILE* file = fopen("output.pl1", "a");
    if (file == NULL) {
        perror("Error: Could not open output.pl1 for writing");
        return;
    }

    fprintf(stderr, "Generating declarations...\n");
    printDeclarations(file);

    fprintf(stderr, "Generating main code...\n");
    printNode(tree, file, 0);
    fprintf(file, ";\n");

    fclose(file);
    fprintf(stderr, "Code generation complete: output.pl1\n");
    return;
}
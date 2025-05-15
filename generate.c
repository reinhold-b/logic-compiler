
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symboltable.h"
#include "syntaxtree.h"

void printArgsReversed(Node* arg, FILE* file, int* first) {
    if (!arg) return;


    // First recurse into next argument
    printArgsReversed(arg->types.argumentType.nextArg, file, first);

    // Now print this argument
    if (!*first) {
        fprintf(file, ",");
    } else {
        *first = 0;
    }

    // Now print this argument
    Node* funcArg = arg->types.argumentType.value;
    if (funcArg && funcArg->nodeType == NODE_FUNCTION) {
        SymTableEntry* fEntry = funcArg->types.functionType.symEntry;
        fprintf(file, "%s(", fEntry->identifier);

        Node* fArg = funcArg->types.functionType.arg;
        int first = 1;
        while (fArg != NULL) {
            if (!first) fprintf(file, ",");
            first = 0;
            if (fArg->types.argumentType.symEntry)
                fprintf(file, "%s", fArg->types.argumentType.symEntry->publicName);
            else
                fprintf(file, "<null>");
            fArg = fArg->types.argumentType.nextArg;
        }
        fprintf(file, ")");
    }
    else if (arg->types.argumentType.symEntry) {
        fprintf(file, "%s", arg->types.argumentType.symEntry->publicName);
    }
    else {
        fprintf(file, "<null>");
    }
}

const char* typeToString(SymTableType type) {
    switch (type) {
        case Predicate: return "Predicate";
        case Function: return "Function";
        case Var: return "Var";
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

void printNode(Node* node, FILE* file, int recursionLevel) {
    if (!node) {
        fprintf(stderr, "DEBUG[%d]: NULL node encountered\n", recursionLevel);
        return;
    }

    fprintf(stderr, "DEBUG[%d]: Visiting node of type %d\n", recursionLevel, node->nodeType);

    switch (node->nodeType) {
        case NODE_UNARY: {
            ++recursionLevel;
            fprintf(stderr, "DEBUG[%d]: Generating code for unary node\n", recursionLevel);
            fprintf(file, "~");
            if (node->types.unaryType.child) {
                printNode(node->types.unaryType.child, file, recursionLevel);
            } else {
                fprintf(stderr, "DEBUG[%d]: Unary node has no child\n", recursionLevel);
            }
            break;
        }

        case NODE_BINARY: {
            ++recursionLevel;
            fprintf(stderr, "DEBUG[%d]: Generating code for binary node\n", recursionLevel);
            if (node->types.binaryType.left) {
                fprintf(file, "(");
                printNode(node->types.binaryType.left, file, recursionLevel);
                fprintf(file, ")");
            } else {
                fprintf(stderr, "DEBUG[%d]: Binary node has no left child\n", recursionLevel);
            }

            fprintf(file, " %s ", operatorToSymbol(node->types.binaryType.operator));
            if (strcmp(node->types.binaryType.operator, "AND") == 0) {
                fprintf(file, "\n");
            }

            if (node->types.binaryType.right) {
                fprintf(file, "(");
                printNode(node->types.binaryType.right, file, recursionLevel);
                fprintf(file, ")");
            } else {
                fprintf(stderr, "DEBUG[%d]: Binary node has no right child\n", recursionLevel);
            }
            break;
        }

        case NODE_PREDICATE: {
            fprintf(stderr, "DEBUG[%d]: Generating code for predicate node\n", recursionLevel);
            SymTableEntry* entry = node->types.predicateType.symEntry;
            if (entry) {
                fprintf(file, "%s(", entry->identifier);
                Node* arg = node->types.predicateType.arg;
                
                int first = 1;
                printArgsReversed(arg, file, &first); 
                fprintf(file, ")");
            } else {
                fprintf(stderr, "DEBUG[%d]: Predicate node has null symEntry\n", recursionLevel);
            }
            break;
        }

        case NODE_QUANTOR: {
            ++recursionLevel;
            fprintf(stderr, "DEBUG[%d]: Generating code for quantor node\n", recursionLevel);
            SymTableEntry* entry = node->types.quantorType.entry;
            if (entry) {
                fprintf(file, "%s[%s](", typeToString(entry->type), entry->publicName);
                if (node->types.quantorType.child) {
                    printNode(node->types.quantorType.child, file, recursionLevel);
                } else {
                    fprintf(stderr, "DEBUG[%d]: Quantor node has no child\n", recursionLevel);
                }
                fprintf(file, ")");
            } else {
                fprintf(stderr, "DEBUG[%d]: Quantor node has null entry\n", recursionLevel);
            }
            break;
        }

        case NODE_NUMBER: {
            fprintf(stderr, "DEBUG[%d]: Generating code for number node (%d)\n",
                    recursionLevel, node->types.numberType.value);
            fprintf(file, "%d", node->types.numberType.value);
            break;
        }

        case NODE_ARG: {
            fprintf(stderr, "DEBUG[%d]: Generating code for argument node\n", recursionLevel);
            if (node->types.argumentType.symEntry) {
                fprintf(stderr, "DEBUG[%d]: Argument symEntry = %s\n",
                        recursionLevel, node->types.argumentType.symEntry->identifier);
            } else {
                fprintf(stderr, "DEBUG[%d]: Argument node has null symEntry\n", recursionLevel);
            }
            if (node->types.argumentType.nextArg) {
                printNode(node->types.argumentType.nextArg, file, recursionLevel + 1);
            }
            break;
        }

        case NODE_TRUE:
            fprintf(stderr, "DEBUG[%d]: Gen for true node\n", recursionLevel);
            fprintf(file, "TRUE");
            break;

        case NODE_FALSE:
            fprintf(stderr, "DEBUG[%d]: Gen for false node\n", recursionLevel);
            fprintf(file, "FALSE");
            break;

        default: {
            fprintf(stderr, "DEBUG[%d]: Unknown node type %d\n", recursionLevel, node->nodeType);
            break;
        }
    }
}


void printDeclarations(FILE* file) {
    SymTable symTable = table;
    fprintf(file, "\n\n");
    for (int i = 0; i < tableAdr; i++) {
        char type[20];
        char* id = symTable.entries[i].identifier;
        fprintf(stderr, "%s", id);
        int arity = symTable.entries[i].arity;
        switch (symTable.entries[i].type)
        {
        case 0:
            strcpy(type, "PREDICATE");
            break;
        case 1:
            strcpy(type, "FUNCTION");
            break;
        case 2:
            strcpy(type, "VARIABLE");
            break;
        default:
            strcpy(type, "UNKNOWN");
            break;
        }
        if (strcmp("UNKNOWN", type) != 0) {
            if (strcmp("VARIABLE", type) == 0) {
                fprintf(file, "DECLARE %s %s : int\n", type, id);
            } else {
                fprintf(file, "DECLARE %s %s : %d\n", type, id, arity);
            }
        }
    }
    fprintf(file, "\n");
}

void generateCode(Node* tree) {
    FILE *file = fopen("output.pl1", "a"); // "w" = write (überschreibt Datei)
    if (file == NULL) {
        perror("Datei konnte nicht geöffnet werden");
        return;
    }
    fprintf(stderr, "Generating declarations...\n");
    printDeclarations(file);
    fprintf(stderr, "Generating code...\n");
    printNode(tree, file, 0);
    fprintf(file, ";");
    fclose(file);
    return;
    
}



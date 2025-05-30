#include "symboltable.h"
#include "syntaxtree.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


Node* makeNode(int nodeType, ...) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Failed");
        return NULL;
    }

    newNode->nodeType = nodeType;

    va_list args;
    va_start(args, nodeType);

    switch (nodeType) {
        case NODE_UNARY:
            newNode->types.unaryType.child = va_arg(args, Node*);
            break;
        case NODE_BINARY:
            newNode->types.binaryType.left = va_arg(args, Node*);
            newNode->types.binaryType.right = va_arg(args, Node*);
            newNode->types.binaryType.operator = va_arg(args, char*);
            break;
        case NODE_PREDICATE:
            newNode->types.predicateType.symEntry = va_arg(args, SymTableEntry*);
            newNode->types.predicateType.arg = va_arg(args, Node*);
            break;
        case NODE_QUANTOR:
            newNode->types.quantorType.entry = va_arg(args, SymTableEntry*);
            newNode->types.quantorType.child = va_arg(args, Node*);
            break;
        case NODE_FUNCTION:
            newNode->types.functionType.symEntry = va_arg(args, SymTableEntry*);
            newNode->types.functionType.arg = va_arg(args, Node*); 
            break;
        case NODE_VARIABLE:
            newNode->types.variableType.symEntry = va_arg(args, SymTableEntry*);
            break;
        case NODE_TRUE:
            break;
        case NODE_FALSE:
            break;
        case NODE_NUMBER:
            newNode->types.numberType.value = va_arg(args, int);
            break;

        case NODE_SIMPLE_ARGUMENT:
            newNode->types.simpleArgumentType.symEntry = va_arg(args, SymTableEntry*);
            newNode->types.simpleArgumentType.nextArg = va_arg(args, Node*);
            break;

        case NODE_FUNCTION_ARGUMENT:
            newNode->types.functionArgumentType.functionCallNode = va_arg(args, Node*);
            newNode->types.functionArgumentType.nextArg = va_arg(args, Node*);
            break;

        default:
            fprintf(stderr, "makeNode: Uknown nodeType %d\n", nodeType);
            free(newNode);
            newNode = NULL;
            break;
    }

    va_end(args);
    return newNode;
}


void printTree(Node* node, int recursionLevel) {
    if (!node) return;

    for (int i = 0; i < recursionLevel * 2; i++) {
        printf(".");
    }

    switch (node->nodeType) {
        case NODE_UNARY:
            printf("Unary node\n");
            if (node->types.unaryType.child)
                printTree(node->types.unaryType.child, recursionLevel + 1);
            break;

        case NODE_BINARY:
            printf("Binary node: %s\n", node->types.binaryType.operator);
            if (node->types.binaryType.left)
                printTree(node->types.binaryType.left, recursionLevel + 1);
            if (node->types.binaryType.right)
                printTree(node->types.binaryType.right, recursionLevel + 1);
            break;

        case NODE_PREDICATE:
            if (node->types.predicateType.symEntry) {
                printf("Predicate node: %s\n", node->types.predicateType.symEntry->identifier);
                Node* currentArg = node->types.predicateType.arg;
                while (currentArg != NULL) {
                    printTree(currentArg, recursionLevel + 1); 
                    if (currentArg->nodeType == NODE_SIMPLE_ARGUMENT) {
                        currentArg = currentArg->types.simpleArgumentType.nextArg;
                    } else if (currentArg->nodeType == NODE_FUNCTION_ARGUMENT) {
                        currentArg = currentArg->types.functionArgumentType.nextArg;
                    } else {
                        fprintf(stderr, "printTree: Unexpected type in argument list of predicate: %d\n", currentArg->nodeType);
                        break;
                    }
                }
            }
            else
                printf("Predicate node: <null symEntry>\n");
            break;

        case NODE_QUANTOR:
            if (node->types.quantorType.entry)
                printf("Quantor node: %s\n", node->types.quantorType.entry->identifier);
            else
                printf("Quantor node: <null entry>\n");
            if (node->types.quantorType.child)
                printTree(node->types.quantorType.child, recursionLevel + 1);
            break;

        case NODE_FUNCTION:
            if (node->types.functionType.symEntry) {
                printf("Function node: %s\n", node->types.functionType.symEntry->identifier);
                Node* currentArg = node->types.functionType.arg;
                while (currentArg != NULL) {
                    printTree(currentArg, recursionLevel + 1);
                    if (currentArg->nodeType == NODE_SIMPLE_ARGUMENT) {
                        currentArg = currentArg->types.simpleArgumentType.nextArg;
                    } else if (currentArg->nodeType == NODE_FUNCTION_ARGUMENT) {
                        currentArg = currentArg->types.functionArgumentType.nextArg;
                    } else {
                        fprintf(stderr, "printTree: Unexpected nodeType in argument list of function: %d\n", currentArg->nodeType);
                        break;
                    }
                }
            } else {
                printf("Function node: <null symEntry>\n");
            }
            break;

        case NODE_NUMBER:
            printf("Number node: %d\n", node->types.numberType.value);
            break;

        case NODE_SIMPLE_ARGUMENT:
            if (node->types.simpleArgumentType.symEntry) {
                printf("Argument node (Simple): %s\n", node->types.simpleArgumentType.symEntry->identifier);
            } else {
                printf("Argument node (Simple): <null symEntry>\n");
            }
            break;

        case NODE_FUNCTION_ARGUMENT:
            printf("Argument node (Function Call)\n");
            if (node->types.functionArgumentType.functionCallNode) {
                printTree(node->types.functionArgumentType.functionCallNode, recursionLevel + 1);
            } else {
                for (int i = 0; i < (recursionLevel + 1) * 2; i++) { printf("."); }
                printf("Function node: <null functionCallNode>\n");
            }
            break;

        case NODE_TRUE:
            printf("TRUE NODE\n");
            break;
        case NODE_FALSE:
            printf("FALSE NODE\n");
            break;
        default:
            printf("Other node type: %d\n", node->nodeType);
            break;
    }
}


int traverse(Node* current_arg) {
    if (current_arg == NULL) return 0;

    int count = 0;
    Node* next = NULL;

    if (current_arg->nodeType == NODE_SIMPLE_ARGUMENT) {
        count = 1;
        next = current_arg->types.simpleArgumentType.nextArg;
    } else if (current_arg->nodeType == NODE_FUNCTION_ARGUMENT) {
        count = 1;
        next = current_arg->types.functionArgumentType.nextArg;
    } else {
        fprintf(stderr, "traverse: Unexpected node type in argument list: %d\n", current_arg->nodeType);
        return 0;
    }

    return count + traverse(next);
}

int countArgumentsOfNode(Node* node) {
    if (node == NULL) return 0;

    Node* arg_list_head = NULL;

    if (node->nodeType == NODE_FUNCTION) {
        arg_list_head = node->types.functionType.arg;
    }
    else if (node->nodeType == NODE_PREDICATE) {
        arg_list_head = node->types.predicateType.arg;
    }
    else {
        fprintf(stderr, "countArgumentsOfNode called on non-function/predicate node type: %d\n", node->nodeType);
        return 0;
    }

    return traverse(arg_list_head);
}
#include "symboltable.h"
#include "syntaxtree.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


Node* makeNode(int nodeType, ...) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;

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
            // No data needed
            break;
        case NODE_FALSE:
            // No data needed
            break;
        case NODE_NUMBER:
            newNode->types.numberType.value = va_arg(args, int);
            break;
        case NODE_ARG:
            newNode->types.argumentType.symEntry = va_arg(args, SymTableEntry*);
            newNode->types.argumentType.nextArg = va_arg(args, Node*);
            newNode->types.argumentType.value   = va_arg(args, Node*); // the function
        
            if (newNode->types.argumentType.value &&
                newNode->types.argumentType.value->nodeType == NODE_FUNCTION) {
                printf("mkFcArgNode: storing function %s\n",
                    newNode->types.argumentType.value->types.functionType.symEntry->identifier);
            }
           break;
        default:
            // Handle unknown type
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
                printTree(node->types.unaryType.child, ++recursionLevel);
            break;

        case NODE_BINARY:
            printf("Binary node: %s\n", node->types.binaryType.operator);
            ++recursionLevel;
            if (node->types.binaryType.left)
                printTree(node->types.binaryType.left, recursionLevel);
            if (node->types.binaryType.right)
                printTree(node->types.binaryType.right, recursionLevel);
            break;

        case NODE_PREDICATE:
            if (node->types.predicateType.symEntry) {
                printf("Predicate node: %s\n", node->types.predicateType.symEntry->identifier);
                printTree(node->types.predicateType.arg, ++recursionLevel);
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
                printTree(node->types.quantorType.child, ++recursionLevel);
            break;

        case NODE_FUNCTION:
            if (node->types.functionType.symEntry) {
                printf("Function node: %s\n", node->types.functionType.symEntry->identifier);
                printTree(node->types.functionType.arg, ++recursionLevel);
            } else {
                printf("Function node: <null symEntry>\n");
            }
            break;

        case NODE_NUMBER:
            printf("Number node: %d\n", node->types.numberType.value);
            break;

        case NODE_ARG:
            if (node->types.argumentType.symEntry) {
                printf("Argument node symentry: %s\n", node->types.argumentType.symEntry->identifier);
            } else {
                printf("Argument node symentry: <null> Entry\n");
            }
            if (node->types.argumentType.nextArg) {
                printTree(node->types.argumentType.nextArg, ++recursionLevel);
            }
            if (node->types.argumentType.value &&
                node->types.argumentType.value->nodeType == NODE_FUNCTION) {
                SymTableEntry* sym = node->types.argumentType.value->types.functionType.symEntry;
                printf("Function in ARG: %s\n", sym->identifier);
                printTree(node->types.argumentType.value, recursionLevel + 1); // optional: show inside func
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

int countArgumentsOfNode(Node* node) {
    if (node->nodeType == NODE_FUNCTION) {
        if (node->types.functionType.arg == NULL) return 0;
        return traverse(node->types.functionType.arg);
    }
    else if (node->nodeType == NODE_PREDICATE) {
        if (node->types.predicateType.arg == NULL) return 0;
        return traverse(node->types.predicateType.arg);
    }
    return 0;
}

int traverse(Node* node) {
    Node* nextArg = node->types.argumentType.nextArg; 
    if (nextArg) return 1 + traverse(nextArg);
    else return 1;
}

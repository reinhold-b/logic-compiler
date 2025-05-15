#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include "symboltable.h"

// Node type constants
#define NODE_UNARY 1
#define NODE_BINARY 2
#define NODE_PREDICATE 3
#define NODE_QUANTOR 4
#define NODE_FUNCTION 5
#define NODE_VARIABLE 6
#define NODE_TRUE 7
#define NODE_FALSE 8
#define NODE_NUMBER 9
#define NODE_ARG 10

// Macros to create different types of nodes
#define mkUnaryNode(child) makeNode(NODE_UNARY, child)
#define mkBinaryNode(left, right, operator) makeNode(NODE_BINARY, left, right, operator)
#define mkPredicateNode(entry, arguments) makeNode(NODE_PREDICATE, entry, arguments)
#define mkQuantorNode(entry, node) makeNode(NODE_QUANTOR, entry, node)
#define mkFunctionNode(entry, arguments) makeNode(NODE_FUNCTION, entry, arguments)
#define mkVariableNode(entry) makeNode(NODE_VARIABLE, entry)
#define mkTrueNode() makeNode(NODE_TRUE)
#define mkFalseNode() makeNode(NODE_FALSE)
#define mkNumberNode(value) makeNode(NODE_NUMBER, value)
#define mkArgNode(value, arguments) makeNode(NODE_ARG, value, arguments, NULL)
#define mkFcArgNode(func, next) makeNode(NODE_ARG, NULL, next, func)

// Forward declarations
typedef struct Node Node;
typedef struct SyntaxTree SyntaxTree;


struct Node {
    int nodeType;
    union {
        struct {
            Node* child;
        } unaryType;
       struct {
            Node* left;
            Node* right;
            char* operator;
        } binaryType;
        struct {
            SymTableEntry* symEntry;
            Node* arg;
        } predicateType;
        struct {
            SymTableEntry* entry;
            Node* child;
        } quantorType;
        struct {
            SymTableEntry* symEntry;
            Node* arg;
        } functionType;
        struct {
            SymTableEntry* symEntry;
        } variableType;
        struct {
            int value;
        } numberType;
        struct {
            SymTableEntry* symEntry;
            Node* nextArg;
            Node* value;
        } argumentType;
        // trueType and falseType can stay empty
    } types;
};

struct SyntaxTree {
    Node* root;
};

// Function declarations
Node* makeNode(int nodeType, ...);
void printTree(Node* node, int recursionLevel);
int countArgumentsOfNode(Node* node);
int traverse(Node* node);

#endif // SYNTAXTREE_H

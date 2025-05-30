#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include "symboltable.h"

#define NODE_UNARY 1
#define NODE_BINARY 2
#define NODE_PREDICATE 3
#define NODE_QUANTOR 4
#define NODE_FUNCTION 5
#define NODE_VARIABLE 6
#define NODE_TRUE 7
#define NODE_FALSE 8
#define NODE_NUMBER 9
#define NODE_SIMPLE_ARGUMENT 10
#define NODE_FUNCTION_ARGUMENT 11

#define mkUnaryNode(child) makeNode(NODE_UNARY, child)
#define mkBinaryNode(left, right, operator) makeNode(NODE_BINARY, left, right, operator)
#define mkPredicateNode(entry, arguments) makeNode(NODE_PREDICATE, entry, arguments)
#define mkQuantorNode(entry, node) makeNode(NODE_QUANTOR, entry, node)
#define mkFunctionNode(entry, arguments) makeNode(NODE_FUNCTION, entry, arguments)
#define mkVariableNode(entry) makeNode(NODE_VARIABLE, entry)
#define mkTrueNode() makeNode(NODE_TRUE)
#define mkFalseNode() makeNode(NODE_FALSE)
#define mkNumberNode(value) makeNode(NODE_NUMBER, value)

#define mkArgNode(sym_entry, next_arg_node) makeNode(NODE_SIMPLE_ARGUMENT, sym_entry, next_arg_node)
#define mkFcArgNode(func_node, next_arg_node) makeNode(NODE_FUNCTION_ARGUMENT, func_node, next_arg_node)


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
        } simpleArgumentType;

        struct {
            Node* functionCallNode;
            Node* nextArg;
        } functionArgumentType;

    } types;
};

struct SyntaxTree {
    Node* root;
};

Node* makeNode(int nodeType, ...);
void printTree(Node* node, int recursionLevel);
int countArgumentsOfNode(Node* node);
int traverse(Node* node);

#endif
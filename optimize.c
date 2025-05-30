#include "syntaxtree.h"
#include "optimize.h"
#include "symboltable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Node* cloneArgumentListInternal(Node* arg_head) {
    if (!arg_head) return NULL;

    Node* newHead = NULL;
    Node* currentNew = NULL;
    Node* currentOriginal = arg_head;

    while (currentOriginal != NULL) {
        Node* clonedArgNode = malloc(sizeof(Node));
        if (!clonedArgNode) {
            fprintf(stderr, "Out of memory in cloneArgumentListInternal.\n");
            exit(EXIT_FAILURE);
        }

        clonedArgNode->nodeType = currentOriginal->nodeType;

        if (currentOriginal->nodeType == NODE_SIMPLE_ARGUMENT) {
            clonedArgNode->types.simpleArgumentType.symEntry = currentOriginal->types.simpleArgumentType.symEntry;
            clonedArgNode->types.simpleArgumentType.nextArg = NULL;
        } else if (currentOriginal->nodeType == NODE_FUNCTION_ARGUMENT) {
            clonedArgNode->types.functionArgumentType.functionCallNode = cloneNode(currentOriginal->types.functionArgumentType.functionCallNode);
            clonedArgNode->types.functionArgumentType.nextArg = NULL;
        } else {
            fprintf(stderr, "ERROR: cloneArgumentListInternal encountered unexpected node type %d.\n", currentOriginal->nodeType);
            free(clonedArgNode);
            exit(EXIT_FAILURE);
        }

        if (!newHead) {
            newHead = clonedArgNode;
        } else {
            if (currentNew->nodeType == NODE_SIMPLE_ARGUMENT) {
                currentNew->types.simpleArgumentType.nextArg = clonedArgNode;
            } else if (currentNew->nodeType == NODE_FUNCTION_ARGUMENT) {
                currentNew->types.functionArgumentType.nextArg = clonedArgNode;
            }
        }
        currentNew = clonedArgNode;

        if (currentOriginal->nodeType == NODE_SIMPLE_ARGUMENT) {
            currentOriginal = currentOriginal->types.simpleArgumentType.nextArg;
        } else if (currentOriginal->nodeType == NODE_FUNCTION_ARGUMENT) {
            currentOriginal = currentOriginal->types.functionArgumentType.nextArg;
        } else {
            currentOriginal = NULL;
        }
    }
    return newHead;
}

Node* cloneNode(Node* node) {
    if (!node) return NULL;

    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Out of memory in cloneNode.\n");
        exit(EXIT_FAILURE);
    }

    newNode->nodeType = node->nodeType;

    switch (node->nodeType) {
        case NODE_UNARY:
            newNode->types.unaryType.child = cloneNode(node->types.unaryType.child);
            break;

        case NODE_BINARY:
            newNode->types.binaryType.left = cloneNode(node->types.binaryType.left);
            newNode->types.binaryType.right = cloneNode(node->types.binaryType.right);
            newNode->types.binaryType.operator = strdup(node->types.binaryType.operator);
            break;

        case NODE_QUANTOR:
            newNode->types.quantorType.child = cloneNode(node->types.quantorType.child);
            newNode->types.quantorType.entry = node->types.quantorType.entry;
            break;

        case NODE_PREDICATE:
            newNode->types.predicateType.symEntry = node->types.predicateType.symEntry;
            newNode->types.predicateType.arg = cloneArgumentListInternal(node->types.predicateType.arg);
            break;

        case NODE_FUNCTION:
            newNode->types.functionType.symEntry = node->types.functionType.symEntry;
            newNode->types.functionType.arg = cloneArgumentListInternal(node->types.functionType.arg);
            break;

        case NODE_SIMPLE_ARGUMENT:
            newNode->types.simpleArgumentType.symEntry = node->types.simpleArgumentType.symEntry;
            newNode->types.simpleArgumentType.nextArg = cloneNode(node->types.simpleArgumentType.nextArg);
            break;

        case NODE_FUNCTION_ARGUMENT:
            newNode->types.functionArgumentType.functionCallNode = cloneNode(node->types.functionArgumentType.functionCallNode);
            newNode->types.functionArgumentType.nextArg = cloneNode(node->types.functionArgumentType.nextArg);
            break;

        case NODE_VARIABLE:
            newNode->types.variableType.symEntry = node->types.variableType.symEntry;
            break;

        case NODE_NUMBER:
            newNode->types.numberType.value = node->types.numberType.value;
            break;

        case NODE_TRUE:
        case NODE_FALSE:
            break;

        default:
            fprintf(stderr, "Unknown node type in cloneNode: %d\n", node->nodeType);
            exit(EXIT_FAILURE);
    }

    return newNode;
}

Node* optimizeArgumentList(Node* arg_head, Node* (*optimize_func)(Node*)) {
    if (!arg_head) return NULL;

    Node* newHead = NULL;
    Node* currentNew = NULL;
    Node* currentOriginal = arg_head;

    while (currentOriginal != NULL) {
        Node* processedArgNode = currentOriginal;

        if (currentOriginal->nodeType == NODE_SIMPLE_ARGUMENT) {
            processedArgNode->types.simpleArgumentType.nextArg = optimizeArgumentList(currentOriginal->types.simpleArgumentType.nextArg, optimize_func);
        } else if (currentOriginal->nodeType == NODE_FUNCTION_ARGUMENT) {
            processedArgNode->types.functionArgumentType.functionCallNode = optimize_func(currentOriginal->types.functionArgumentType.functionCallNode);
            processedArgNode->types.functionArgumentType.nextArg = optimizeArgumentList(currentOriginal->types.functionArgumentType.nextArg, optimize_func);
        } else {
            fprintf(stderr, "ERROR: optimizeArgumentList encountered unexpected node type %d (expected argument node).\n", currentOriginal->nodeType);
            break;
        }

        if (!newHead) {
            newHead = processedArgNode;
        }
        currentNew = processedArgNode;

        if (currentOriginal->nodeType == NODE_SIMPLE_ARGUMENT) {
            currentOriginal = currentOriginal->types.simpleArgumentType.nextArg;
        } else if (currentOriginal->nodeType == NODE_FUNCTION_ARGUMENT) {
            currentOriginal = currentOriginal->types.functionArgumentType.nextArg;
        } else {
            currentOriginal = NULL;
        }
    }
    return newHead;
}


Node* removeDoubleNeg(Node* node) {
    if (node == NULL) return NULL;

    switch (node->nodeType) {
        case NODE_UNARY: {
            node->types.unaryType.child = removeDoubleNeg(node->types.unaryType.child);
            if (node->types.unaryType.child != NULL && node->types.unaryType.child->nodeType == NODE_UNARY) {
                Node* grandchild = node->types.unaryType.child->types.unaryType.child;
                return removeDoubleNeg(grandchild);
            }
            return node;
        }
        case NODE_BINARY:
            node->types.binaryType.left = removeDoubleNeg(node->types.binaryType.left);
            node->types.binaryType.right = removeDoubleNeg(node->types.binaryType.right);
            return node;
        case NODE_QUANTOR:
            node->types.quantorType.child = removeDoubleNeg(node->types.quantorType.child);
            return node;
        case NODE_PREDICATE:
            node->types.predicateType.arg = optimizeArgumentList(node->types.predicateType.arg, removeDoubleNeg);
            return node;
        case NODE_FUNCTION:
            node->types.functionType.arg = optimizeArgumentList(node->types.functionType.arg, removeDoubleNeg);
            return node;

        case NODE_SIMPLE_ARGUMENT:
            node->types.simpleArgumentType.nextArg = removeDoubleNeg(node->types.simpleArgumentType.nextArg);
            return node;
        case NODE_FUNCTION_ARGUMENT:
            node->types.functionArgumentType.functionCallNode = removeDoubleNeg(node->types.functionArgumentType.functionCallNode);
            node->types.functionArgumentType.nextArg = removeDoubleNeg(node->types.functionArgumentType.nextArg);
            return node;

        case NODE_VARIABLE:
        case NODE_TRUE:
        case NODE_FALSE:
        case NODE_NUMBER:
        default:
            return node;
    }
}

Node* pushNegationsToPredicates(Node* node) {
    if (node == NULL) return NULL;

    if (node->nodeType == NODE_UNARY) {
        Node* child = node->types.unaryType.child;
        if (child == NULL) {
            return node;
        }

        if (child->nodeType == NODE_PREDICATE) {
            return node;
        }

        if (child->nodeType == NODE_UNARY) {
            Node* grandChild = child->types.unaryType.child;
            return pushNegationsToPredicates(grandChild);
        }

        if (child->nodeType == NODE_BINARY) {
            const char* op = child->types.binaryType.operator;
            Node* left = child->types.binaryType.left;
            Node* right = child->types.binaryType.right;
            Node* newNode;

            Node* negLeft = pushNegationsToPredicates(mkUnaryNode(left));
            Node* negRight = pushNegationsToPredicates(mkUnaryNode(right));

            if (strcmp(op, "AND") == 0) {
                newNode = mkBinaryNode(negLeft, negRight, "OR");
            } else if (strcmp(op, "OR") == 0) {
                newNode = mkBinaryNode(negLeft, negRight, "AND");
            } else {
                fprintf(stderr, "Warning: Unexpected operator %s under negation in pushNegationsToPredicates.\n", op);
                node->types.unaryType.child = child;
                return node;
            }
            return newNode;
        }

        if (child->nodeType == NODE_QUANTOR) {
            SymTableEntry* quantorEntry = child->types.quantorType.entry;
            if (quantorEntry) {
                quantorEntry->type = (quantorEntry->type == Q_all) ? Q_exists : Q_all;
            } else {
                fprintf(stderr, "Error: Quantor entry not found for negation pushdown.\n");
                exit(EXIT_FAILURE);
            }

            Node* grandChild = child->types.quantorType.child;
            Node* negGrandChild = pushNegationsToPredicates(mkUnaryNode(grandChild));

            Node* newNode = mkQuantorNode(quantorEntry, negGrandChild);
            return newNode;
        }

        switch (child->nodeType) {
            case NODE_FUNCTION:
                break;

            case NODE_SIMPLE_ARGUMENT:
            case NODE_FUNCTION_ARGUMENT:
                 fprintf(stderr, "Warning: UNARY node has an ARGUMENT node type (%d) as a direct child in pushNegationsToPredicates. This is an unexpected AST structure.\n", child->nodeType);
                 break;

            case NODE_VARIABLE:
            case NODE_NUMBER:
            case NODE_TRUE:
            case NODE_FALSE:
                break;
            default:
                fprintf(stderr, "Warning: Unexpected node type %d under negation in pushNegationsToPredicates during recursion.\n", child->nodeType);
                break;
        }
        node->types.unaryType.child = child;
        return node;

    } else {
        switch (node->nodeType) {
            case NODE_BINARY:
                node->types.binaryType.left = pushNegationsToPredicates(node->types.binaryType.left);
                node->types.binaryType.right = pushNegationsToPredicates(node->types.binaryType.right);
                break;
            case NODE_QUANTOR:
                node->types.quantorType.child = pushNegationsToPredicates(node->types.quantorType.child);
                break;
            case NODE_PREDICATE:
                node->types.predicateType.arg = optimizeArgumentList(node->types.predicateType.arg, pushNegationsToPredicates);
                break;
            case NODE_FUNCTION:
                node->types.functionType.arg = optimizeArgumentList(node->types.functionType.arg, pushNegationsToPredicates);
                break;

            case NODE_SIMPLE_ARGUMENT:
                node->types.simpleArgumentType.nextArg = pushNegationsToPredicates(node->types.simpleArgumentType.nextArg);
                break;
            case NODE_FUNCTION_ARGUMENT:
                node->types.functionArgumentType.functionCallNode = pushNegationsToPredicates(node->types.functionArgumentType.functionCallNode);
                node->types.functionArgumentType.nextArg = pushNegationsToPredicates(node->types.functionArgumentType.nextArg);
                break;

            case NODE_VARIABLE:
            case NODE_NUMBER:
            case NODE_TRUE:
            case NODE_FALSE:
                break;
            default:
                fprintf(stderr, "Warning: Unknown node type %d in pushNegationsToPredicates during recursion.\n", node->nodeType);
                break;
        }
        return node;
    }
}


Node* removeImplicationsAndEquivalences(Node* node) {
    if (node == NULL) return NULL;

    switch (node->nodeType) {
        case NODE_BINARY: {
            Node* left = removeImplicationsAndEquivalences(node->types.binaryType.left);
            Node* right = removeImplicationsAndEquivalences(node->types.binaryType.right);

            const char* op = node->types.binaryType.operator;
            Node* newNode = node;

            if (strcmp(op, "IMPLIES") == 0) {
                Node* leftCopy = cloneNode(left);
                Node* notA = mkUnaryNode(leftCopy);
                newNode = mkBinaryNode(notA, right, "OR");
                return removeImplicationsAndEquivalences(newNode);
            } else if (strcmp(op, "EQUALS") == 0) {
                Node* leftCopy1 = cloneNode(left);
                Node* rightCopy1 = cloneNode(right);
                Node* leftCopy2 = cloneNode(left);
                Node* rightCopy2 = cloneNode(right);

                Node* notA = mkUnaryNode(leftCopy1);
                Node* notB = mkUnaryNode(rightCopy1);
                Node* and1 = mkBinaryNode(leftCopy2, rightCopy2, "AND");
                Node* and2 = mkBinaryNode(notA, notB, "AND");
                newNode = mkBinaryNode(and1, and2, "OR");
                return removeImplicationsAndEquivalences(newNode);
            } else {
                node->types.binaryType.left = left;
                node->types.binaryType.right = right;
                return node;
            }
        }

        case NODE_UNARY:
            node->types.unaryType.child = removeImplicationsAndEquivalences(node->types.unaryType.child);
            return node;

        case NODE_QUANTOR:
            node->types.quantorType.child = removeImplicationsAndEquivalences(node->types.quantorType.child);
            return node;

        case NODE_PREDICATE:
            node->types.predicateType.arg = optimizeArgumentList(node->types.predicateType.arg, removeImplicationsAndEquivalences);
            return node;

        case NODE_FUNCTION:
            node->types.functionType.arg = optimizeArgumentList(node->types.functionType.arg, removeImplicationsAndEquivalences);
            return node;

        case NODE_SIMPLE_ARGUMENT:
            node->types.simpleArgumentType.nextArg = removeImplicationsAndEquivalences(node->types.simpleArgumentType.nextArg);
            return node;
        case NODE_FUNCTION_ARGUMENT:
            node->types.functionArgumentType.functionCallNode = removeImplicationsAndEquivalences(node->types.functionArgumentType.functionCallNode);
            node->types.functionArgumentType.nextArg = removeImplicationsAndEquivalences(node->types.functionArgumentType.nextArg);
            return node;

        case NODE_VARIABLE:
        case NODE_TRUE:
        case NODE_FALSE:
        case NODE_NUMBER:
        default:
            return node;
    }
}

Node* evaluateBooleanOperators(Node* node) {
    if (node == NULL) return NULL;

    switch (node->nodeType) {
        case NODE_UNARY: {
            Node* child = evaluateBooleanOperators(node->types.unaryType.child);
            if (child == NULL) {
                return node;
            }

            if (child->nodeType == NODE_TRUE) {
                return mkFalseNode();
            }
            if (child->nodeType == NODE_FALSE) {
                return mkTrueNode();
            }
            node->types.unaryType.child = child;
            return node;
        }

        case NODE_BINARY: {
            Node* left = evaluateBooleanOperators(node->types.binaryType.left);
            Node* right = evaluateBooleanOperators(node->types.binaryType.right);
            const char* op = node->types.binaryType.operator;

            if (left == NULL || right == NULL) {
                fprintf(stderr, "Error: NULL child in binary node during boolean evaluation.\n");
                node->types.binaryType.left = left;
                node->types.binaryType.right = right;
                return node;
            }

            Node* result = node;

            if (strcmp(op, "AND") == 0) {
                if (left->nodeType == NODE_FALSE || right->nodeType == NODE_FALSE) {
                    result = mkFalseNode();
                } else if (left->nodeType == NODE_TRUE) {
                    result = right;
                } else if (right->nodeType == NODE_TRUE) {
                    result = left;
                }
            } else if (strcmp(op, "OR") == 0) {
                if (left->nodeType == NODE_TRUE || right->nodeType == NODE_TRUE) {
                    result = mkTrueNode();
                } else if (left->nodeType == NODE_FALSE) {
                    result = right;
                } else if (right->nodeType == NODE_FALSE) {
                    result = left;
                }
            }

            if (result != node) {
            } else {
                node->types.binaryType.left = left;
                node->types.binaryType.right = right;
            }
            return result;
        }

        case NODE_QUANTOR:
            node->types.quantorType.child = evaluateBooleanOperators(node->types.quantorType.child);
            if (node->types.quantorType.child != NULL) {
                if (node->types.quantorType.child->nodeType == NODE_TRUE && node->types.quantorType.entry->type == Q_all) {
                    return mkTrueNode();
                }
                if (node->types.quantorType.child->nodeType == NODE_FALSE && node->types.quantorType.entry->type == Q_exists) {
                    return mkFalseNode();
                }
            }
            return node;

        case NODE_PREDICATE:
        case NODE_FUNCTION:
            if (node->nodeType == NODE_PREDICATE) {
                node->types.predicateType.arg = optimizeArgumentList(node->types.predicateType.arg, evaluateBooleanOperators);
            } else {
                node->types.functionType.arg = optimizeArgumentList(node->types.functionType.arg, evaluateBooleanOperators);
            }
            return node;

        case NODE_SIMPLE_ARGUMENT:
            node->types.simpleArgumentType.nextArg = evaluateBooleanOperators(node->types.simpleArgumentType.nextArg);
            return node;
        case NODE_FUNCTION_ARGUMENT:
            node->types.functionArgumentType.functionCallNode = evaluateBooleanOperators(node->types.functionArgumentType.functionCallNode);
            node->types.functionArgumentType.nextArg = evaluateBooleanOperators(node->types.functionArgumentType.nextArg);
            return node;

        case NODE_VARIABLE:
        case NODE_TRUE:
        case NODE_FALSE:
        case NODE_NUMBER:
        default:
            return node;
    }
}
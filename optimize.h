#ifndef OPTIMIZE_H
#define OPTIMIZE_H

#include "syntaxtree.h"
#include "symboltable.h"

Node* optimizeArgumentList(Node* arg_head, Node* (*optimize_func)(Node*));
Node* removeDoubleNeg(Node* node);
Node* pushNegationsToPredicates(Node* node);

Node* removeImplicationsAndEquivalences(Node* node);

Node* evaluateBooleanOperators(Node* node);

Node* cloneNode(Node* node);

#endif // OPTIMIZE_H
#ifndef GENERATE_H
#define GENERATE_H

#include <stdio.h>
#include "symboltable.h"
#include "syntaxtree.h"

void generateCode(Node* tree);
void printNode(Node* node);
const char* typeToString(SymTableType type);
const char* operatorToSymbol(char* operatorString);
void printDeclarations(FILE* file); 
void printArgsReversed(Node* arg, FILE* file, int* first);

#endif
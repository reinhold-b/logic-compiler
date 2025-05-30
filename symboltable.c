#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"


SymTable table;
int tableAdr = 0;

void addSymEntry(char* identifier, char* publicName, SymTableType type, int arity) {
    for (int i = 0; i < tableAdr; i++) {
        if (strcmp(table.entries[i].identifier, identifier) == 0) {
            fprintf(stderr, "WARN: %s already declared as %u, now overwritten with %u\n",
                identifier, table.entries[i].type, type);
            table.entries[i].type = type;
            table.entries[i].arity = arity;
            return;
        }
    }

    if (tableAdr >= 100) {
        fprintf(stderr, "ERROR: Symbol table full\n");
        return;
    }

    SymTableEntry entry;
    strcpy(entry.identifier, identifier);
    strcpy(entry.publicName, publicName);
    entry.type = type;
    entry.arity = arity;

    table.entries[tableAdr++] = entry;
}

void printTable() {
    SymTableEntry e;
    for (int i = 0; i < LEN(table.entries); i++) {
        e = table.entries[i];
        printf("%s", e.identifier);
        printf("%d", e.arity);
        printf("%u", e.type);
        printf("\n");
    }
}

void removeSymEntry(char* identifier) {
    int holeAdr = -1;

    for (int i = 0; i < tableAdr; i++) {
        if (strcmp(table.entries[i].identifier, identifier) == 0) {
            holeAdr = i;
            break;
        }
    }

    if (holeAdr == -1) return

    free(table.entries[holeAdr].identifier);

    for (int i = holeAdr; i < tableAdr - 1; i++) {
        table.entries[i] = table.entries[i + 1];
    }

    tableAdr--;
}

SymTableEntry* getSymEntry(char* id) {
    SymTableEntry* entry;
    for (int i = 0; i < tableAdr; i++) {
        if (strcmp(table.entries[i].identifier, id) == 0) {
            return &table.entries[i];
            break;
        }
    }
    return NULL;
}

void clearSymbolTable() {
    tableAdr = 0;
    fprintf(stderr, "SYT: Symbol table cleared.\n");
}






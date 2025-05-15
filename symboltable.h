#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define LEN(x) sizeof(x) / sizeof(x[0])

typedef enum {
    Predicate,
    Function,
    Var,
    Q_all,
    Q_exists,
    Argument,
} SymTableType;

typedef struct SymTableEntry {
    char identifier[30];
    char publicName[30];
    SymTableType type;
    int arity;
} SymTableEntry;

typedef struct {
    SymTableEntry entries[100];
} SymTable;


extern SymTable table;
extern int tableAdr;

void addSymEntry(char* identifier, char* publicName, SymTableType type, int arity);
void removeSymEntry(char* identifier);
void printTable();
SymTableEntry* getSymEntry(char* id);
void clearSymbolTable();

#endif

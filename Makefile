#**********************************************
#*                                            *
#*     Project: pl1c                          *
#*     Module:  Makefile                      *
#*                                            *
#*     (c) 2021 by Klaus Wieland              *
#*                                            *
#**********************************************

# Object files
objects = parser.o scanner.o symboltable.o syntaxtree.o generate.o optimize.o

# Compiler and tools
CC   = gcc
LEX  = flex
YACC = bison

# Default target
all: pl1c

# Link the executable
pl1c: $(objects)
	$(CC) -o $@ $^

# Generate parser source and header from Bison file
parser.c parser.h: parser.y
	$(YACC) -d -o parser.c parser.y

# Generate scanner source from Flex file
scanner.c: scanner.l
	$(LEX) -t scanner.l > scanner.c

# Compile object files
parser.o: parser.c parser.h syntaxtree.h symboltable.h
	$(CC) -c parser.c

scanner.o: scanner.c parser.h
	$(CC) -c scanner.c

symboltable.o: symboltable.c symboltable.h
	$(CC) -c symboltable.c

syntaxtree.o: syntaxtree.c syntaxtree.h symboltable.h
	$(CC) -c syntaxtree.c

generate.o: generate.c generate.h syntaxtree.h symboltable.h
	$(CC) -c generate.c

optimize.o: optimize.c optimize.h syntaxtree.h symboltable.h
	$(CC) -c optimize.c

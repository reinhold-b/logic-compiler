#include "syntaxtree.h"
#include "optimize.h"
#include "symboltable.h" // Für SymTableEntry und Typen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Annahme: Diese Funktionen sind in syntaxtree.c/h implementiert:
// Node* mkUnaryNode(Node* child);
// Node* mkBinaryNode(Node* left, Node* right, const char* operator);
// Node* mkPredicateNode(SymTableEntry* entry, Node* arg);
// Node* mkQuantorNode(SymTableEntry* entry, Node* child);
// Node* mkFunctionNode(SymTableEntry* entry, Node* arg);
// Node* mkVariableNode(SymTableEntry* entry);
// Node* mkNumberNode(int value);
// Node* mkTrueNode();
// Node* mkFalseNode();
// Node* mkArgNode(SymTableEntry* entry, Node* nextArg); // Für Variablen/Strings als Argumente
// Node* mkArgValueNode(Node* value, Node* nextArg); // Für komplexere Knoten als Argumente (z.B. Funktionsaufrufe, Literale)
// void freeSyntaxTree(Node* node); // Funktion zum Freigeben eines Baumes (nicht in diesem Code verwendet, da free() entfernt wurde)
// const char* typeToString(SymTableType type); // Hilfsfunktion zur Konvertierung von SymTableType in String


/**
 * @brief Erstellt eine tiefe Kopie eines Syntaxbaumknotens und seiner Kindknoten.
 * @param node Der zu klonende Knoten.
 * @return Ein Zeiger auf den neu erstellten geklonten Knoten.
 */
Node* cloneNode(Node* node) {
    if (!node) return NULL;

    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Out of memory in cloneNode.\n");
        exit(EXIT_FAILURE);
    }

    // Grundlegende Felder kopieren
    memcpy(newNode, node, sizeof(Node));

    // Rekursive Klonung von Kindknoten und tiefe Kopie von Strings, falls notwendig
    switch (node->nodeType) {
        case NODE_UNARY:
            newNode->types.unaryType.child = cloneNode(node->types.unaryType.child);
            break;

        case NODE_BINARY:
            newNode->types.binaryType.left = cloneNode(node->types.binaryType.left);
            newNode->types.binaryType.right = cloneNode(node->types.binaryType.right);
            // Tiefe Kopie des Operator-Strings, falls dynamisch allokiert (angenommen)
            newNode->types.binaryType.operator = strdup(node->types.binaryType.operator);
            break;

        case NODE_QUANTOR:
            newNode->types.quantorType.child = cloneNode(node->types.quantorType.child);
            // Symbol-Eintrag nicht klonen, denselben Eintrag wiederverwenden (dieselbe quantifizierte Variable)
            break;

        case NODE_PREDICATE:
        case NODE_FUNCTION:
            // Argumentliste klonen
            if (node->nodeType == NODE_PREDICATE) {
                 newNode->types.predicateType.arg = cloneNode(node->types.predicateType.arg);
            } else { // NODE_FUNCTION
                 newNode->types.functionType.arg = cloneNode(node->types.functionType.arg);
            }
            // Symbol-Eintrag für Prädikat-/Funktionsnamen wiederverwenden
            break;

        case NODE_ARG:
            // Wert des Arguments und den Rest der Argumentliste klonen
            newNode->types.argumentType.value = cloneNode(node->types.argumentType.value);
            newNode->types.argumentType.nextArg = cloneNode(node->types.argumentType.nextArg);
            // Symbol-Eintrag für die Argumentvariable/den String muss möglicherweise geklont oder sorgfältig behandelt werden,
            // je nachdem, wie Argument-Symbol-Einträge verwaltet werden. Vorerst Wiederverwendung angenommen.
            break;

        case NODE_VARIABLE:
        case NODE_NUMBER:
        case NODE_TRUE:
        case NODE_FALSE:
            // Dies sind Blattknoten oder einfache Literale, keine Kindknoten oder dynamische Allokation zum Klonen
            break;

        default:
            fprintf(stderr, "Unknown node type in cloneNode: %d\n", node->nodeType);
            // In einer realen Anwendung wäre eine robustere Fehlerbehandlung als das Beenden wünschenswert
            exit(EXIT_FAILURE);
    }

    return newNode;
}


/**
 * @brief Rekursive Funktion zur Optimierung des Syntaxbaums.
 * Entfernt doppelte Negationen (~~A => A).
 * @param node Der Wurzelknoten des zu optimierenden Teilbaums.
 * @return Der neue Wurzelknoten des optimierten Teilbaums.
 */
Node* removeDoubleNeg(Node* node) {
    if (node == NULL) return NULL;

    switch (node->nodeType) {
        case NODE_UNARY: {
            node->types.unaryType.child = removeDoubleNeg(node->types.unaryType.child);
            // Prüfen auf doppelte Negation nach der Rekursion
            if (node->types.unaryType.child != NULL && node->types.unaryType.child->nodeType == NODE_UNARY) {
                Node* grandchild = node->types.unaryType.child->types.unaryType.child;
                // Entfernt: free(node->types.unaryType.child); // Innerer Unary-Knoten
                // Entfernt: free(node); // Äußerer Unary-Knoten
                return removeDoubleNeg(grandchild); // Optimierung vom Enkel fortsetzen
            }
            return node; // Return the unary node if no double negation was removed
        }
        case NODE_BINARY:
            node->types.binaryType.left = removeDoubleNeg(node->types.binaryType.left);
            node->types.binaryType.right = removeDoubleNeg(node->types.binaryType.right);
            return node; // Return after processing binary
        case NODE_QUANTOR:
            node->types.quantorType.child = removeDoubleNeg(node->types.quantorType.child);
            return node; // Return after processing quantor
        case NODE_PREDICATE:
        case NODE_FUNCTION:
            // Rekursiv auf Argumente anwenden
            if (node->nodeType == NODE_PREDICATE) {
                node->types.predicateType.arg = removeDoubleNeg(node->types.predicateType.arg);
            } else { // NODE_FUNCTION
                node->types.functionType.arg = removeDoubleNeg(node->types.functionType.arg);
            }
            return node; // Return after processing predicate/function
        case NODE_ARG:
            // Rekursiv auf Argumentwert und nächstes Argument anwenden
            node->types.argumentType.value = removeDoubleNeg(node->types.argumentType.value);
            node->types.argumentType.nextArg = removeDoubleNeg(node->types.argumentType.nextArg);
            return node; // Return after processing arg
        case NODE_VARIABLE:
        case NODE_TRUE:
        case NODE_FALSE:
        case NODE_NUMBER:
        default:
            return node; // Return for literal types
    }
    // This point should not be reached
}

/**
 * @brief Verschiebt Negationen im Syntaxbaum mithilfe der De Morgan'schen Gesetze
 * und Quantor-Negationsregeln in Richtung der Prädikatknoten.
 * @param node Der Wurzelknoten des zu optimierenden Teilbaums.
 * @return Der neue Wurzelknoten des optimierten Teilbaums.
 */
Node* pushNegationsToPredicates(Node* node) {
    if (node == NULL) return NULL;

    if (node->nodeType == NODE_UNARY) {
        Node* child = node->types.unaryType.child;
        if (child == NULL) {
            return node; // Negation ohne Kind
        }

        // Wenn das Kind bereits ein Prädikat ist, Negation nicht weiter verschieben
        if (child->nodeType == NODE_PREDICATE) {
            return node;
        }

        // Doppelte Negation: ~~A -> A (Wird auch von removeDoubleNeg behandelt, aber hier zur Vollständigkeit)
        if (child->nodeType == NODE_UNARY) {
             Node* grandChild = child->types.unaryType.child;
             // Entfernt: free(node->types.unaryType.child);
             // Entfernt: free(node);
             return pushNegationsToPredicates(grandChild);
        }

        // De Morgan'sche Gesetze: ¬(A ∧ B) → ¬A ∨ ¬B, ¬(A ∨ B) → ¬A ∧ ¬B
        if (child->nodeType == NODE_BINARY) {
            const char* op = child->types.binaryType.operator;
            Node* left = child->types.binaryType.left;
            Node* right = child->types.binaryType.right;
            Node* newNode;

            // Negationen rekursiv in die Kindknoten verschieben
            Node* negLeft = pushNegationsToPredicates(mkUnaryNode(left));
            Node* negRight = pushNegationsToPredicates(mkUnaryNode(right));

            // Entfernt: free((void*)child->types.binaryType.operator);
            // Entfernt: free(child);
            // Entfernt: free(node);

            if (strcmp(op, "AND") == 0) {
                newNode = mkBinaryNode(negLeft, negRight, "OR");
            } else if (strcmp(op, "OR") == 0) {
                newNode = mkBinaryNode(negLeft, negRight, "AND");
            } else {
                 fprintf(stderr, "Warning: Unexpected operator %s under negation in pushNegationsToPredicates.\n", op);
                 return NULL; // Oder Fehlerbehandlung
            }
            return newNode; // Return the new binary node
        }

        // Quantor-Negation: ¬∀x A → ∃x ¬A, und ¬∃x A → ∀x ¬A
        if (child->nodeType == NODE_QUANTOR) {
            SymTableEntry* quantorEntry = child->types.quantorType.entry;
            if (quantorEntry) {
                 // Quantor-Typ umkehren
                 quantorEntry->type = (quantorEntry->type == Q_all) ? Q_exists : Q_all;
            } else {
                 fprintf(stderr, "Error: Quantor entry not found for negation pushdown.\n");
                 // Entfernt: free(node); free(child);
                 exit(EXIT_FAILURE);
            }

            Node* grandChild = child->types.quantorType.child;
            // Negation rekursiv in den Enkel verschieben
            Node* negGrandChild = pushNegationsToPredicates(mkUnaryNode(grandChild));

            // Entfernt: free(node);
            // Entfernt: free(child);

            // Neuen Quantor-Knoten erstellen
            Node* newNode = mkQuantorNode(quantorEntry, negGrandChild);
            return newNode; // Return the new quantor node
        }

        // For other node types under negation (functions, variables, constants, arguments),
        // recursively push negation down into their children/values.
        // Negations bei Prädikaten stoppen hier.
        switch (child->nodeType) {
             case NODE_FUNCTION:
                 child->types.functionType.arg = pushNegationsToPredicates(child->types.functionType.arg);
                 break;
             case NODE_ARG:
                 child->types.argumentType.value = pushNegationsToPredicates(child->types.argumentType.value);
                 child->types.argumentType.nextArg = pushNegationsToPredicates(child->types.argumentType.nextArg);
                 break;
             // Für Literale (VARIABLE, NUMBER, TRUE, FALSE) bleibt die Negation darüber
             case NODE_VARIABLE:
             case NODE_NUMBER:
             case NODE_TRUE:
             case NODE_FALSE:
                 break; // Negation stoppt hier
             default:
                 fprintf(stderr, "Warning: Unexpected node type %d under negation in pushNegationsToPredicates during recursion.\n", child->nodeType);
                 break;
        }
        // After processing the child, update the child pointer and return the current unary node
        node->types.unaryType.child = child; // Child might have been replaced by recursive call
        return node; // Return the current unary node

    } else { // Nicht NODE_UNARY
        // Rekursiv in die Kindknoten gehen
        switch (node->nodeType) {
            case NODE_BINARY:
                node->types.binaryType.left = pushNegationsToPredicates(node->types.binaryType.left);
                node->types.binaryType.right = pushNegationsToPredicates(node->types.binaryType.right);
                break;
            case NODE_QUANTOR:
                node->types.quantorType.child = pushNegationsToPredicates(node->types.quantorType.child);
                break;
            case NODE_PREDICATE:
                 node->types.predicateType.arg = pushNegationsToPredicates(node->types.predicateType.arg);
                 break;
            case NODE_FUNCTION:
                 node->types.functionType.arg = pushNegationsToPredicates(node->types.functionType.arg);
                 break;
            case NODE_ARG:
                 node->types.argumentType.value = pushNegationsToPredicates(node->types.argumentType.value);
                 node->types.argumentType.nextArg = pushNegationsToPredicates(node->types.argumentType.nextArg);
                 break;
            case NODE_VARIABLE:
            case NODE_NUMBER:
            case NODE_TRUE:
            case NODE_FALSE:
                break; // Keine Kindknoten, in die rekursiv gegangen werden kann
            default:
                 fprintf(stderr, "Warning: Unknown node type %d in pushNegationsToPredicates during recursion.\n", node->nodeType);
                break;
        }
        return node; // Return the non-unary node after processing children
    }
    // This point should not be reached
}


/**
 * @brief Transformiert Implikationen (A -> B => ~A | B) und Äquivalenzen (A <-> B => (A & B) | (~A & ~B)).
 * Ruft sich rekursiv auf neu erstellten Knoten auf, um eine vollständige Transformation in einem Durchlauf zu gewährleisten.
 * @param node Der Wurzelknoten des zu optimierenden Teilbaums.
 * @return Der neue Wurzelknoten des optimierten Teilbaums.
 */
Node* removeImplicationsAndEquivalences(Node* node) {
    if (node == NULL) return NULL;

    switch (node->nodeType) {
        case NODE_BINARY: {
            // Rekursive Entfernung von Implikationen und Äquivalenzen zuerst in den Kindknoten
            Node* left = removeImplicationsAndEquivalences(node->types.binaryType.left);
            Node* right = removeImplicationsAndEquivalences(node->types.binaryType.right);

            const char* op = node->types.binaryType.operator;
            Node* newNode = node; // Annahme: Wir geben standardmäßig den aktuellen Knoten zurück

            if (strcmp(op, "IMPLIES") == 0) {
                // A -> B  ≡  ~A ∨ B
                Node* leftCopy = cloneNode(left); // Linken Teil für Negation klonen
                Node* notA = mkUnaryNode(leftCopy);
                newNode = mkBinaryNode(notA, right, "OR");
                // Entfernt: free((void*)node->types.binaryType.operator);
                // Entfernt: free(node);
                // WICHTIG: Rekursive Bearbeitung des neu erstellten OR-Knotens
                return removeImplicationsAndEquivalences(newNode);
            } else if (strcmp(op, "EQUALS") == 0) {
                // A <-> B  ≡  (A ∧ B) ∨ (~A ∧ ~B)
                Node* leftCopy1 = cloneNode(left);
                Node* rightCopy1 = cloneNode(right);
                Node* leftCopy2 = cloneNode(left);
                Node* rightCopy2 = cloneNode(right);

                Node* notA = mkUnaryNode(leftCopy1);
                Node* notB = mkUnaryNode(rightCopy1);
                Node* and1 = mkBinaryNode(leftCopy2, rightCopy2, "AND");
                Node* and2 = mkBinaryNode(notA, notB, "AND");
                newNode = mkBinaryNode(and1, and2, "OR");
                 // Entfernt: free((void*)node->types.binaryType.operator);
                // Entfernt: free(node);
                 // WICHTIG: Rekursive Bearbeitung des neu erstellten OR-Knotens (der ANDs enthält)
                return removeImplicationsAndEquivalences(newNode);
            } else {
                // Andere binäre Operatoren: Kindknoten sind bereits bearbeitet, nur aktualisieren und aktuellen Knoten zurückgeben
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
        case NODE_FUNCTION:
             if (node->nodeType == NODE_PREDICATE) {
                 node->types.predicateType.arg = removeImplicationsAndEquivalences(node->types.predicateType.arg);
             } else { // NODE_FUNCTION
                 node->types.functionType.arg = removeImplicationsAndEquivalences(node->types.functionType.arg);
             }
             return node;

        case NODE_ARG:
             node->types.argumentType.value = removeImplicationsAndEquivalences(node->types.argumentType.value);
             node->types.argumentType.nextArg = removeImplicationsAndEquivalences(node->types.argumentType.nextArg);
             return node;

        case NODE_VARIABLE:
        case NODE_TRUE:
        case NODE_FALSE:
        case NODE_NUMBER:
        default:
            return node;
    }
}


/**
 * @brief Wertet boolesche Operationen mit konstanten Operanden aus (z.B. TRUE & FALSE => FALSE).
 * @param node Der Wurzelknoten des zu optimierenden Teilbaums.
 * @return Der neue Wurzelknoten des optimierten Teilbaums.
 */
Node* evaluateBooleanOperators(Node* node) {
    if (node == NULL) return NULL;

    switch (node->nodeType) {
        case NODE_UNARY: {
            Node* child = evaluateBooleanOperators(node->types.unaryType.child);
            if (child == NULL) return node;

            if (child->nodeType == NODE_TRUE) {
                return mkFalseNode();
            }
            if (child->nodeType == NODE_FALSE) {
                 return mkTrueNode();
            }
            node->types.unaryType.child = child;
            return node; // Return after processing unary
        }

        case NODE_BINARY: {
            Node* left = evaluateBooleanOperators(node->types.binaryType.left);
            Node* right = evaluateBooleanOperators(node->types.binaryType.right);
            const char* op = node->types.binaryType.operator;

            if (left == NULL || right == NULL) {
                 fprintf(stderr, "Error: NULL child in binary node during boolean evaluation.\n");
                 return NULL; // Error case
            }

            if (strcmp(op, "AND") == 0) {
                if (left->nodeType == NODE_FALSE || right->nodeType == NODE_FALSE) {
                     return mkFalseNode();
                }
                if (left->nodeType == NODE_TRUE) {
                     return right;
                }
                if (right->nodeType == NODE_TRUE) {
                    return left;
                }
            } else if (strcmp(op, "OR") == 0) {
                if (left->nodeType == NODE_TRUE || right->nodeType == NODE_TRUE) {
                     return mkTrueNode();
                }
                if (left->nodeType == NODE_FALSE) {
                    return right;
                }
                if (right->nodeType == NODE_FALSE) {
                    return left;
                }
            }
            // If no simplification occurred for AND/OR or if it's another binary operator
            node->types.binaryType.left = left;
            node->types.binaryType.right = right;
            return node; // Return after processing binary
        }

        case NODE_QUANTOR:
            node->types.quantorType.child = evaluateBooleanOperators(node->types.quantorType.child);
            return node; // Return after processing quantor

        case NODE_PREDICATE:
        case NODE_FUNCTION:
             if (node->nodeType == NODE_PREDICATE) {
                 node->types.predicateType.arg = evaluateBooleanOperators(node->types.predicateType.arg);
             } else { // NODE_FUNCTION
                 node->types.functionType.arg = evaluateBooleanOperators(node->types.functionType.arg);
             }
             return node; // Return after processing predicate/function

        case NODE_ARG:
             node->types.argumentType.value = evaluateBooleanOperators(node->types.argumentType.value);
             node->types.argumentType.nextArg = evaluateBooleanOperators(node->types.argumentType.nextArg);
             return node; // Return after processing arg

        case NODE_VARIABLE:
        case NODE_TRUE:
        case NODE_FALSE:
        case NODE_NUMBER:
        default:
            return node; // Return for literal/unhandled types
    }
    // This point should not be reached
}

// Die Funktionen toPrenexForm und pullQuantors sind hier nicht enthalten,
// da sie nicht explizit in den vier angeforderten Optimierungen genannt wurden.

// Annahme: cloneNode ist in syntaxtree.c implementiert
// Node* cloneNode(Node* node);

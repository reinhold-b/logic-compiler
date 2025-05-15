#ifndef OPTIMIZE_H
#define OPTIMIZE_H

#include "syntaxtree.h" // syntaxtree.h einbinden, da Optimierungsfunktionen auf Node-Strukturen arbeiten
#include "symboltable.h" // Für SymTableEntry und Typen


/**
 * @brief Rekursive Funktion zur Optimierung des Syntaxbaums.
 * Entfernt doppelte Negationen (~~A => A).
 * @param node Der Wurzelknoten des zu optimierenden Teilbaums.
 * @return Der neue Wurzelknoten des optimierten Teilbaums.
 */
Node* removeDoubleNeg(Node* node);

/**
 * @brief Verschiebt Negationen im Syntaxbaum mithilfe der De Morgan'schen Gesetze
 * und Quantor-Negationsregeln in Richtung der Prädikatknoten.
 * @param node Der Wurzelknoten des zu optimierenden Teilbaums.
 * @return Der neue Wurzelknoten des optimierten Teilbaums.
 */
Node* pushNegationsToPredicates(Node* node);


/**
 * @brief Transformiert Implikationen (A -> B => ~A | B) und Äquivalenzen (A <-> B => (A & B) | (~A & ~B)).
 * Ruft sich rekursiv auf neu erstellten Knoten auf, um eine vollständige Transformation in einem Durchlauf zu gewährleisten.
 * @param node Der Wurzelknoten des zu optimierenden Teilbaums.
 * @return Der neue Wurzelknoten des optimierten Teilbaums.
 */
Node* removeImplicationsAndEquivalences(Node* node);

/**
 * @brief Wertet boolesche Operationen mit konstanten Operanden aus (z.B. TRUE & FALSE => FALSE).
 * @param node Der Wurzelknoten des zu optimierenden Teilbaums.
 * @return Der neue Wurzelknoten des optimierten Teilbaums.
 */
Node* evaluateBooleanOperators(Node* node);


Node* cloneNode(Node* node);


// Annahme: cloneNode ist in syntaxtree.c/h implementiert
// Node* cloneNode(Node* node);


#endif // OPTIMIZE_H

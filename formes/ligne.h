/**
 * @file ligne.h
 * @brief Interface publique de la gestion des lignes.
 *
 * Déclare le type Line et les fonctions permettant de créer, afficher,
 * modifier, supprimer et exporter en SVG des lignes. Ces fonctions sont
 * appelées depuis main.c.
 */

#ifndef LIGNE_H
#define LIGNE_H

#include <stdio.h>

/**
 * @brief Représente une ligne (un segment).
 *
 * La ligne est définie par ses deux extrémités. Dans le SVG, l'origine est
 * en haut à gauche et l'axe Y est dirigé vers le bas.
 */
typedef struct
{
    double x1;   /**< Abscisse du point de départ. */
    double y1;   /**< Ordonnée du point de départ. */
    double x2;   /**< Abscisse du point d'arrivée. */
    double y2;   /**< Ordonnée du point d'arrivée. */
    int couleur; /**< Indice de la couleur dans PALETTE. */
} Line;

/**
 * @brief Demande les informations d'une ligne et l'ajoute à la liste.
 *
 * Demande X1, Y1, X2, Y2 puis la couleur. Affiche une erreur si le nombre
 * maximum de lignes est atteint ou si l'allocation mémoire échoue.
 */
void ask_for_line(void);

/**
 * @brief Affiche toutes les lignes, numérotées à partir de 1.
 *
 * Affiche un message d'erreur s'il n'y a aucune ligne.
 */
void print_line(void);

/**
 * @brief Modifie une ligne choisie par l'utilisateur.
 *
 * Affiche la liste, demande un numéro, puis propose de changer X1, Y1,
 * X2, Y2 ou la couleur jusqu'à ce que l'utilisateur sorte du sous-menu.
 */
void modify_line(void);

/**
 * @brief Supprime une ligne choisie par l'utilisateur.
 *
 * Affiche la liste, demande un numéro, puis libère la mémoire de la ligne
 * et la retire de la liste.
 */
void delete_line(void);

/**
 * @brief Libère la mémoire de toutes les lignes.
 *
 * À appeler une seule fois, à la fin du programme.
 */
void free_all_lines(void);

/**
 * @brief Écrit toutes les lignes dans un fichier SVG déjà ouvert.
 *
 * Chaque ligne devient un élément <line>, dessiné avec un trait (stroke).
 *
 * @param f Fichier SVG ouvert en écriture (par l'appelant, avec fopen).
 */
void write_svg_line(FILE *f);

#endif
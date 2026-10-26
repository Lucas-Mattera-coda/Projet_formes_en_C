/**
 * @file ellipse.h
 * @brief Interface publique de la gestion des ellipses.
 *
 * Déclare le type Ellipse et les fonctions permettant de créer, afficher,
 * modifier, supprimer et exporter en SVG des ellipses. Ces fonctions sont
 * appelées depuis main.c.
 */

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <stdio.h>

/**
 * @brief Représente une ellipse.
 *
 * L'ellipse est repérée par son centre et ses deux rayons. Dans le SVG,
 * l'origine est en haut à gauche et l'axe Y est dirigé vers le bas.
 */
typedef struct
{
    double x;        /**< Abscisse du centre. */
    double y;        /**< Ordonnée du centre. */
    double radius_x; /**< Rayon horizontal. */
    double radius_y; /**< Rayon vertical. */
    int couleur;     /**< Indice de la couleur dans PALETTE. */
} Ellipse;

/**
 * @brief Demande les informations d'une ellipse et l'ajoute à la liste.
 *
 * Demande X, Y, les deux rayons puis la couleur. Affiche une erreur si le
 * nombre maximum d'ellipses est atteint ou si l'allocation mémoire échoue.
 */
void ask_for_ellipse(void);

/**
 * @brief Affiche toutes les ellipses, numérotées à partir de 1.
 *
 * Affiche un message d'erreur s'il n'y a aucune ellipse.
 */
void print_ellipse(void);

/**
 * @brief Modifie une ellipse choisie par l'utilisateur.
 *
 * Affiche la liste, demande un numéro, puis propose de changer X, Y,
 * l'un des rayons ou la couleur jusqu'à ce que l'utilisateur sorte du
 * sous-menu.
 */
void modify_ellipse(void);

/**
 * @brief Supprime une ellipse choisie par l'utilisateur.
 *
 * Affiche la liste, demande un numéro, puis libère la mémoire de l'ellipse
 * et la retire de la liste.
 */
void delete_ellipse(void);

/**
 * @brief Libère la mémoire de toutes les ellipses.
 *
 * À appeler une seule fois, à la fin du programme.
 */
void free_all_ellipse(void);

/**
 * @brief Écrit toutes les ellipses dans un fichier SVG déjà ouvert.
 *
 * Chaque ellipse devient un élément <ellipse>.
 *
 * @param f Fichier SVG ouvert en écriture (par l'appelant, avec fopen).
 */
void write_svg_ellipse(FILE *f);

#endif
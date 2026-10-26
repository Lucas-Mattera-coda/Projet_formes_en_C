/**
 * @file carre.h
 * @brief Interface publique de la gestion des carrés.
 *
 * Déclare le type Square et les fonctions permettant de créer, afficher,
 * modifier, supprimer et exporter en SVG des carrés. Ces fonctions sont
 * appelées depuis main.c.
 */

#ifndef CARRE_H
#define CARRE_H

#include <stdio.h>

/**
 * @brief Représente un carré.
 *
 * Le carré est repéré par son coin supérieur gauche. Dans le SVG, l'origine
 * est en haut à gauche et l'axe Y est dirigé vers le bas.
 */
typedef struct
{
    double x;    /**< Abscisse du coin supérieur gauche. */
    double y;    /**< Ordonnée du coin supérieur gauche. */
    double side; /**< Longueur du côté. */
    int couleur; /**< Indice de la couleur dans PALETTE. */
} Square;

/**
 * @brief Demande les informations d'un carré et l'ajoute à la liste.
 *
 * Demande X, Y, le côté puis la couleur. Affiche une erreur si le nombre
 * maximum de carrés est atteint ou si l'allocation mémoire échoue.
 */
void ask_for_square(void);

/**
 * @brief Affiche tous les carrés, numérotés à partir de 1.
 *
 * Affiche un message d'erreur s'il n'y a aucun carré.
 */
void print_square(void);

/**
 * @brief Modifie un carré choisi par l'utilisateur.
 *
 * Affiche la liste, demande un numéro, puis propose de changer X, Y,
 * le côté ou la couleur jusqu'à ce que l'utilisateur sorte du sous-menu.
 */
void modify_square(void);

/**
 * @brief Supprime un carré choisi par l'utilisateur.
 *
 * Affiche la liste, demande un numéro, puis libère la mémoire du carré
 * et le retire de la liste.
 */
void delete_square(void);

/**
 * @brief Libère la mémoire de tous les carrés.
 *
 * À appeler une seule fois, à la fin du programme.
 */
void free_all_square(void);

/**
 * @brief Écrit tous les carrés dans un fichier SVG déjà ouvert.
 *
 * Chaque carré devient un élément <rect> de même largeur et hauteur.
 *
 * @param f Fichier SVG ouvert en écriture (par l'appelant, avec fopen).
 */
void write_svg_square(FILE *f);

#endif
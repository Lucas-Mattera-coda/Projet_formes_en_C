/**
 * @file rectangle.h
 * @brief Interface publique de la gestion des rectangles.
 *
 * Déclare le type Rectangle et les fonctions permettant de créer, afficher,
 * modifier, supprimer et exporter en SVG des rectangles. Ces fonctions sont
 * appelées depuis main.c.
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdio.h>

/**
 * @brief Représente un rectangle.
 *
 * Le rectangle est repéré par son coin supérieur gauche. Dans le SVG,
 * l'origine est en haut à gauche et l'axe Y est dirigé vers le bas.
 */
typedef struct
{
    double x;      /**< Abscisse du coin supérieur gauche. */
    double y;      /**< Ordonnée du coin supérieur gauche. */
    double width;  /**< Largeur. */
    double height; /**< Hauteur. */
    int couleur;   /**< Indice de la couleur dans PALETTE. */
} Rectangle;

/**
 * @brief Demande les informations d'un rectangle et l'ajoute à la liste.
 *
 * Demande X, Y, la largeur, la hauteur puis la couleur. Affiche une erreur
 * si le nombre maximum de rectangles est atteint ou si l'allocation mémoire
 * échoue.
 */
void ask_for_rectangle(void);

/**
 * @brief Affiche tous les rectangles, numérotés à partir de 1.
 *
 * Affiche un message d'erreur s'il n'y a aucun rectangle.
 */
void print_rectangle(void);

/**
 * @brief Modifie un rectangle choisi par l'utilisateur.
 *
 * Affiche la liste, demande un numéro, puis propose de changer X, Y,
 * la largeur, la hauteur ou la couleur jusqu'à ce que l'utilisateur sorte
 * du sous-menu.
 */
void modify_rectangle(void);

/**
 * @brief Supprime un rectangle choisi par l'utilisateur.
 *
 * Affiche la liste, demande un numéro, puis libère la mémoire du rectangle
 * et le retire de la liste.
 */
void delete_rectangle(void);

/**
 * @brief Libère la mémoire de tous les rectangles.
 *
 * À appeler une seule fois, à la fin du programme.
 */
void free_all_rectangle(void);

/**
 * @brief Écrit tous les rectangles dans un fichier SVG déjà ouvert.
 *
 * Chaque rectangle devient un élément <rect>.
 *
 * @param f Fichier SVG ouvert en écriture (par l'appelant, avec fopen).
 */
void write_svg_rectangle(FILE *f);

#endif
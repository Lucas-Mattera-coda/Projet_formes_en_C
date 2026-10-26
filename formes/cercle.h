/**
 * @file cercle.h
 * @brief Interface publique de la gestion des cercles.
 *
 * Déclare le type Circle et les fonctions permettant de créer, afficher,
 * modifier, supprimer et exporter en SVG des cercles. Ces fonctions sont
 * appelées depuis main.c.
 */

#ifndef CERCLE_H
#define CERCLE_H

#include <stdio.h>

/**
 * @brief Représente un cercle.
 *
 * Le cercle est repéré par son centre. Dans le SVG, l'origine est en haut
 * à gauche et l'axe Y est dirigé vers le bas.
 */
typedef struct
{
    double x;      /**< Abscisse du centre. */
    double y;      /**< Ordonnée du centre. */
    double radius; /**< Rayon du cercle. */
    int couleur;   /**< Indice de la couleur dans PALETTE. */
} Circle;

/**
 * @brief Demande les informations d'un cercle et l'ajoute à la liste.
 *
 * Demande X, Y, le rayon puis la couleur. Affiche une erreur si le nombre
 * maximum de cercles est atteint ou si l'allocation mémoire échoue.
 */
void ask_for_circle(void);

/**
 * @brief Affiche tous les cercles, numérotés à partir de 1.
 *
 * Affiche un message d'erreur s'il n'y a aucun cercle.
 */
void print_circle(void);

/**
 * @brief Modifie un cercle choisi par l'utilisateur.
 *
 * Affiche la liste, demande un numéro, puis propose de changer X, Y,
 * le rayon ou la couleur jusqu'à ce que l'utilisateur sorte du sous-menu.
 */
void modify_circle(void);

/**
 * @brief Supprime un cercle choisi par l'utilisateur.
 *
 * Affiche la liste, demande un numéro, puis libère la mémoire du cercle
 * et le retire de la liste.
 */
void delete_circle(void);

/**
 * @brief Libère la mémoire de tous les cercles.
 *
 * À appeler une seule fois, à la fin du programme.
 */
void free_all_circle(void);

/**
 * @brief Écrit tous les cercles dans un fichier SVG déjà ouvert.
 *
 * Chaque cercle devient un élément <circle>.
 *
 * @param f Fichier SVG ouvert en écriture (par l'appelant, avec fopen).
 */
void write_svg_circle(FILE *f);

#endif
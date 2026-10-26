/**
 * @file utils.h
 * @brief Fonctions utilitaires partagées par plusieurs fichiers du programme.
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Demande un nombre entier à l'utilisateur.
 *
 * Affiche le message, puis redemande la saisie tant que la valeur entrée
 * n'est pas un entier valide. Le reste de la ligne saisie est ensuite
 * ignoré, ce qui évite que des caractères restants perturbent la saisie
 * suivante.
 *
 * @param prompt Message affiché avant la saisie.
 * @return L'entier saisi.
 */
int read_int(const char *prompt);

#endif
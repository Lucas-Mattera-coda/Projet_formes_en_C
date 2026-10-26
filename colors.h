/**
 * @file couleurs.h
 * @brief Palette de couleurs partagée par toutes les formes.
 *
 * Fournit les codes ANSI pour colorer le texte du terminal, le tableau PALETTE
 * qui associe à chaque couleur son nom, son nom SVG et son code ANSI, et la
 * fonction choisir_couleur() pour en choisir une.
 */

#ifndef COULEURS_H
#define COULEURS_H

/**
 * @name Codes ANSI des couleurs
 * Séquences d'échappement à écrire avec printf() pour colorer le texte
 * dans le terminal. Les numéros en commentaire correspondent à la position
 * de chaque couleur dans PALETTE (en comptant à partir de 1).
 * @{
 */
#define BLACK "\033[30m"        // 1
#define PURPLE "\033[35m"       // 2
#define GRAY "\033[90m"         // 3
#define RED "\033[91m"          // 4
#define GREEN "\033[92m"        // 5
#define YELLOW "\033[93m"       // 6
#define BLUE "\033[94m"         // 7
#define CYAN "\033[96m"         // 8
#define WHITE "\033[97m"        // 9
#define BROWN "\033[38;5;130m"  // 10
#define ORANGE "\033[38;5;208m" // 11
#define PINK "\033[38;5;213m"   // 12
/** @} */

/** Code ANSI qui remet le terminal à sa couleur par défaut. */
#define RESET "\033[0m"

/** Nombre de couleurs disponibles dans PALETTE. */
#define NB_COULEURS 12

/**
 * @brief Décrit une couleur de la palette.
 */
typedef struct
{
    const char *nom;  /**< Nom affiché à l'utilisateur (ex : "Rouge"). */
    const char *svg;  /**< Nom de la couleur utilisable dans un fichier SVG (ex : "red"). */
    const char *ansi; /**< Code ANSI pour écrire en couleur dans le terminal. */
} CouleurDef;

/**
 * @brief Tableau de toutes les couleurs disponibles.
 *
 * Les formes mémorisent un indice (de 0 à NB_COULEURS - 1) dans ce tableau
 * plutôt que la couleur elle-même.
 */
extern const CouleurDef PALETTE[NB_COULEURS];

/**
 * @brief Affiche la palette et demande à l'utilisateur de choisir une couleur.
 *
 * Chaque couleur est affichée avec son numéro (à partir de 1) et dans sa
 * propre couleur. La saisie est redemandée tant que le numéro est invalide.
 *
 * @return L'indice de la couleur choisie dans PALETTE (à partir de 0).
 */
int choisir_couleur(void);

#endif
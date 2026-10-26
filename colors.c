#include <stdio.h>
#include "colors.h"
#include "utils.h"

const CouleurDef PALETTE[NB_COULEURS] = {
    {"Noir", "black", "\033[30m"},               // 1
    {"Violet", "purple", "\033[35m"},            // 2
    {"Gris", "gray", "\033[90m"},                // 3
    {"Rouge", "red", "\033[91m"},                // 4
    {"Vert", "lime", "\033[92m"},                // 5
    {"Jaune", "yellow", "\033[93m"},             // 6
    {"Bleu", "dodgerblue", "\033[94m"},          // 7
    {"Cyan", "aqua", "\033[96m"},                // 8
    {"Blanc", "white", "\033[97m"},              // 9
    {"Marron", "saddlebrown", "\033[38;5;130m"}, // 10
    {"Orange", "orange", "\033[38;5;208m"},      // 11
    {"Rose", "hotpink", "\033[38;5;213m"},       // 12
};

int choisir_couleur(void)
{
    printf("Couleurs disponibles :\n");
    for (int i = 0; i < NB_COULEURS; i++)
        printf("  %d -> %s%s" RESET "\n", i + 1, PALETTE[i].ansi, PALETTE[i].nom);

    int choix = read_int("Votre couleur : ");
    while (choix < 1 || choix > NB_COULEURS)
        choix = read_int(RED "Choix invalide, réessayez : " RESET);
    return choix - 1;
}
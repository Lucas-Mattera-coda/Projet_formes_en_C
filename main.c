/**
 * @file main.c
 * @brief Programme de gestion de formes géométriques avec export SVG.
 *
 * Permet de créer, lister, modifier et supprimer des formes (carré, rectangle,
 * cercle, ellipse, ligne), puis de les visualiser dans un fichier SVG
 * mis à jour après chaque action.
 *
 * Chaque action principale possède son propre menu :
 *   - menu_principale()  : le menu de départ
 *   - menu_creer()       : choisir quelle forme créer
 *   - menu_lister()      : choisir quelles formes lister
 *   - menu_modifier()    : choisir quelle forme modifier
 *   - menu_supprimer()   : choisir quelle forme supprimer
 */

#include <stdio.h>
#include <stdlib.h>
#include "formes/ligne.h"
#include "formes/carre.h"
#include "formes/ellipse.h"
#include "formes/rectangle.h"
#include "formes/cercle.h"
#include "colors.h"
#include "utils.h"

/**
 * @brief Efface l'écran du terminal.
 *
 * Utilise la commande système adaptée : "cls" sous Windows,
 * "clear" sous Linux et macOS.
 */
static void effacer_ecran(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief Met le programme en pause jusqu'à l'appui sur Entrée.
 *
 * Évite que les messages soient effacés par effacer_ecran() avant
 * que l'utilisateur ait pu les lire.
 */
static void attendre_entree(void)
{
    printf(PURPLE "\nAppuyez sur Entrée pour continuer..." RESET);
    getchar();
}

/**
 * @brief Réécrit le fichier formes.svg avec toutes les formes actuelles.
 *
 * Crée une image de 800x600 pixels (origine en haut à gauche, axe Y vers le bas)
 * avec un fond blanc, puis demande à chaque type de forme d'écrire ses éléments.
 * Ce qui est écrit en dernier est dessiné par-dessus.
 *
 * Cette fonction n'affiche rien en cas de succès : elle est appelée après
 * chaque action. Un message d'erreur est affiché si le fichier ne peut pas être créé.
 */
static void exporter_svg(void)
{
    FILE *f = fopen("formes.svg", "w");
    if (f == NULL)
    {
        printf(RED "✗ Impossible de créer formes.svg\n" RESET);
        return;
    }

    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\" viewBox=\"0 0 800 600\">\n");
    fprintf(f, "  <rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n");

    write_svg_square(f);
    write_svg_rectangle(f);
    write_svg_circle(f);
    write_svg_ellipse(f);
    write_svg_line(f);

    fprintf(f, "</svg>\n");
    fclose(f);
}

/**
 * @brief Ouvre formes.svg avec le programme par défaut du système.
 *
 * Met d'abord le fichier à jour avec exporter_svg(), puis lance la commande
 * adaptée au système : "start" (Windows), "open" (macOS) ou "xdg-open" (Linux).
 */
static void voir_svg(void)
{
    exporter_svg();

#ifdef _WIN32
    system("start formes.svg");
#elif defined(__APPLE__)
    system("open formes.svg");
#else
    system("xdg-open formes.svg > /dev/null 2>&1 &");
#endif

    printf(GREEN "✓ Ouverture de formes.svg...\n" RESET);
}

/**
 * @brief Termine une action de création, modification ou suppression.
 *
 * Met le SVG à jour pour refléter le changement, puis fait une pause
 * pour laisser le temps de lire les messages.
 */
static void finir_action(void)
{
    exporter_svg();
    attendre_entree();
}

/**
 * @brief Affiche un message d'erreur après un choix de menu invalide.
 */
static void choix_invalide(void)
{
    printf(RED "✗ Choix invalide, veuillez réessayer\n" RESET);
    attendre_entree();
}

/**
 * @brief Menu de création : choisir la forme à créer.
 *
 * Chaque choix appelle la fonction ask_for_xxx() de la forme,
 * puis met à jour le SVG. Le menu se répète jusqu'à "Retour".
 */
static void menu_creer(void)
{
    int choix;
    do
    {
        effacer_ecran();
        printf(CYAN);
        printf("╭──────────────────────────────╮\n");
        printf("│            CRÉER             │\n");
        printf("├──────────────────────────────┤\n");
        printf("│ 1 ➜ Carré                    │\n");
        printf("│ 2 ➜ Rectangle                │\n");
        printf("│ 3 ➜ Cercle                   │\n");
        printf("│ 4 ➜ Ellipse                  │\n");
        printf("│ 5 ➜ Ligne                    │\n");
        printf("│ 6 ➜ Retour                   │\n");
        printf("╰──────────────────────────────╯\n");
        printf(RESET);
        choix = read_int(PURPLE "\n➜ Votre choix : " RESET);
        printf("\n");

        switch (choix)
        {
        case 1:
            ask_for_square();
            finir_action();
            break;
        case 2:
            ask_for_rectangle();
            finir_action();
            break;
        case 3:
            ask_for_circle();
            finir_action();
            break;
        case 4:
            ask_for_ellipse();
            finir_action();
            break;
        case 5:
            ask_for_line();
            finir_action();
            break;
        case 6:
            break;
        default:
            choix_invalide();
            break;
        }
    } while (choix != 6);
}

/**
 * @brief Menu d'affichage : choisir quelles formes lister.
 *
 * Chaque choix appelle la fonction print_xxx() de la forme.
 * Rien n'est modifié, donc le SVG n'est pas réécrit.
 * Le menu se répète jusqu'à "Retour".
 */
static void menu_lister(void)
{
    int choix;
    do
    {
        effacer_ecran();
        printf(CYAN);
        printf("╭──────────────────────────────╮\n");
        printf("│            LISTER            │\n");
        printf("├──────────────────────────────┤\n");
        printf("│ 1 ➜ Carrés                   │\n");
        printf("│ 2 ➜ Rectangles               │\n");
        printf("│ 3 ➜ Cercles                  │\n");
        printf("│ 4 ➜ Ellipses                 │\n");
        printf("│ 5 ➜ Lignes                   │\n");
        printf("│ 6 ➜ Retour                   │\n");
        printf("╰──────────────────────────────╯\n");
        printf(RESET);
        choix = read_int(PURPLE "\n➜ Votre choix : " RESET);
        printf("\n");

        switch (choix)
        {
        case 1:
            print_square();
            attendre_entree();
            break;
        case 2:
            print_rectangle();
            attendre_entree();
            break;
        case 3:
            print_circle();
            attendre_entree();
            break;
        case 4:
            print_ellipse();
            attendre_entree();
            break;
        case 5:
            print_line();
            attendre_entree();
            break;
        case 6:
            break;
        default:
            choix_invalide();
            break;
        }
    } while (choix != 6);
}

/**
 * @brief Menu de modification : choisir le type de forme à modifier.
 *
 * Chaque choix appelle la fonction modify_xxx() de la forme,
 * puis met à jour le SVG. Le menu se répète jusqu'à "Retour".
 */
static void menu_modifier(void)
{
    int choix;
    do
    {
        effacer_ecran();
        printf(CYAN);
        printf("╭──────────────────────────────╮\n");
        printf("│           MODIFIER           │\n");
        printf("├──────────────────────────────┤\n");
        printf("│ 1 ➜ Carré                    │\n");
        printf("│ 2 ➜ Rectangle                │\n");
        printf("│ 3 ➜ Cercle                   │\n");
        printf("│ 4 ➜ Ellipse                  │\n");
        printf("│ 5 ➜ Ligne                    │\n");
        printf("│ 6 ➜ Retour                   │\n");
        printf("╰──────────────────────────────╯\n");
        printf(RESET);
        choix = read_int(PURPLE "\n➜ Votre choix : " RESET);
        printf("\n");

        switch (choix)
        {
        case 1:
            modify_square();
            finir_action();
            break;
        case 2:
            modify_rectangle();
            finir_action();
            break;
        case 3:
            modify_circle();
            finir_action();
            break;
        case 4:
            modify_ellipse();
            finir_action();
            break;
        case 5:
            modify_line();
            finir_action();
            break;
        case 6:
            break;
        default:
            choix_invalide();
            break;
        }
    } while (choix != 6);
}

/**
 * @brief Menu de suppression : choisir le type de forme à supprimer.
 *
 * Chaque choix appelle la fonction delete_xxx() de la forme,
 * puis met à jour le SVG. Le menu se répète jusqu'à "Retour".
 */
static void menu_supprimer(void)
{
    int choix;
    do
    {
        effacer_ecran();
        printf(CYAN);
        printf("╭──────────────────────────────╮\n");
        printf("│          SUPPRIMER           │\n");
        printf("├──────────────────────────────┤\n");
        printf("│ 1 ➜ Carré                    │\n");
        printf("│ 2 ➜ Rectangle                │\n");
        printf("│ 3 ➜ Cercle                   │\n");
        printf("│ 4 ➜ Ellipse                  │\n");
        printf("│ 5 ➜ Ligne                    │\n");
        printf("│ 6 ➜ Retour                   │\n");
        printf("╰──────────────────────────────╯\n");
        printf(RESET);
        choix = read_int(PURPLE "\n➜ Votre choix : " RESET);
        printf("\n");

        switch (choix)
        {
        case 1:
            delete_square();
            finir_action();
            break;
        case 2:
            delete_rectangle();
            finir_action();
            break;
        case 3:
            delete_circle();
            finir_action();
            break;
        case 4:
            delete_ellipse();
            finir_action();
            break;
        case 5:
            delete_line();
            finir_action();
            break;
        case 6:
            break;
        default:
            choix_invalide();
            break;
        }
    } while (choix != 6);
}

/**
 * @brief Affiche le menu principal et fait tourner le programme.
 *
 * Les options 1 à 4 ouvrent le menu de l'action correspondante,
 * l'option 5 ouvre le SVG, l'option 6 quitte. La fonction se termine
 * quand l'utilisateur choisit "Quitter".
 */
static void menu_principale(void)
{
    int choix;
    do
    {
        effacer_ecran();
        printf(CYAN);
        printf("╭──────────────────────────────╮\n");
        printf("│             MENU             │\n");
        printf("├──────────────────────────────┤\n");
        printf("│ 1 ➜ Créer une forme          │\n");
        printf("│ 2 ➜ Lister les formes        │\n");
        printf("│ 3 ➜ Modifier une forme       │\n");
        printf("│ 4 ➜ Supprimer une forme      │\n");
        printf("│ 5 ➜ Afficher le SVG          │\n");
        printf("│ 6 ➜ Quitter                  │\n");
        printf("╰──────────────────────────────╯\n");
        printf(RESET);
        choix = read_int(PURPLE "\n➜ Votre choix : " RESET);
        printf("\n");

        switch (choix)
        {
        case 1:
            menu_creer();
            break;
        case 2:
            menu_lister();
            break;
        case 3:
            menu_modifier();
            break;
        case 4:
            menu_supprimer();
            break;
        case 5:
            voir_svg();
            attendre_entree();
            break;
        case 6:
            printf(GREEN "✓ À bientôt !\n" RESET);
            break;
        default:
            choix_invalide();
            break;
        }
    } while (choix != 6);
}

/**
 * @brief Point d'entrée du programme.
 *
 * Crée un formes.svg vide, lance les menus, puis libère la mémoire
 * de toutes les formes avant de quitter.
 *
 * @return EXIT_SUCCESS si le programme s'est terminé normalement.
 */
int main(void)
{
    exporter_svg();
    menu_principale();

    free_all_square();
    free_all_rectangle();
    free_all_circle();
    free_all_ellipse();
    free_all_lines();
    return EXIT_SUCCESS;
}
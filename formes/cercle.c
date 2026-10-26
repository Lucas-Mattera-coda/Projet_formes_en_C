#include <stdio.h>
#include <stdlib.h>
#include "cercle.h"
#include "colors.h"

#define MAX_CIRCLE 100

static Circle *circles[MAX_CIRCLE];
static int circle_count = 0;

static void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

static double read_double(const char *prompt)
{
    double v;
    printf("%s", prompt);
    while (scanf("%lf", &v) != 1)
    {
        clear_input();
        printf(RED "Valeur invalide, réessayez : " PURPLE);
    }
    return v;
}

static int read_int(const char *prompt)
{
    int v;
    printf("%s", prompt);
    while (scanf("%d", &v) != 1)
    {
        clear_input();
        printf(RED "Valeur invalide, réessayez : " PURPLE);
    }
    return v;
}

static Circle *create_circle(double x, double y, double radius, int couleur)
{
    Circle *circle = malloc(sizeof(Circle));
    if (circle == NULL)
        return NULL;

    circle->x = x;
    circle->y = y;
    circle->radius = radius;
    circle->couleur = couleur;
    return circle;
}

static void print_one_circle(const Circle *circle)
{
    printf("%sCercle (X = %lf, Y = %lf, Rayon = %lf) [%s]\n" RESET,
           PALETTE[circle->couleur].ansi,
           circle->x, circle->y, circle->radius,
           PALETTE[circle->couleur].nom);
}

void ask_for_circle(void)
{
    if (circle_count >= MAX_CIRCLE)
    {
        printf(RED "Nombre maximum de cercles atteint\n" RESET);
        return;
    }

    printf(PURPLE);
    double x = read_double("Sélectionner X : ");
    double y = read_double("Sélectionner Y : ");
    double radius = read_double("Sélectionner Rayon : ");
    printf(RESET);

    int couleur = choisir_couleur();

    Circle *circle = create_circle(x, y, radius, couleur);
    if (circle == NULL)
    {
        printf(RED "Erreur d'allocation mémoire\n" RESET);
        return;
    }

    circles[circle_count++] = circle;
}

void print_circle(void)
{
    if (circle_count == 0)
    {
        printf(RED "Aucun cercle à afficher\n" RESET);
        return;
    }
    for (int i = 0; i < circle_count; i++)
    {
        printf("[%d] ", i + 1);
        print_one_circle(circles[i]);
    }
}

static int select_circle(void)
{
    if (circle_count == 0)
    {
        printf(RED "Aucun cercle disponible\n" RESET);
        return -1;
    }
    print_circle();
    printf(PURPLE);
    int n = read_int("Numéro du cercle : ");
    printf(RESET);

    if (n < 1 || n > circle_count)
    {
        printf(RED "Numéro invalide\n" RESET);
        return -1;
    }
    return n - 1;
}

void modify_circle(void)
{
    int index = select_circle();
    if (index < 0)
        return;

    Circle *circle = circles[index];

    int choice;
    do
    {
        printf(PURPLE "\nQue souhaitez-vous modifier ?\n"
                      "\t1. X\n\t2. Y\n\t3. Rayon\n\t4. Couleur\n\t0. Sortir\n");
        choice = read_int("\tChoix : ");
        printf(RESET);

        switch (choice)
        {
        case 1:
            circle->x = read_double("Nouveau X : ");
            break;
        case 2:
            circle->y = read_double("Nouveau Y : ");
            break;
        case 3:
            circle->radius = read_double("Nouveau rayon : ");
            break;
        case 4:
            circle->couleur = choisir_couleur();
            break;
        case 0:
            break;
        default:
            printf(RED "Choix invalide, veuillez réessayer\n" RESET);
            break;
        }
    } while (choice != 0);
}

void delete_circle(void)
{
    int index = select_circle();
    if (index < 0)
        return;

    free(circles[index]);

    for (int i = index; i < circle_count - 1; i++)
        circles[i] = circles[i + 1];

    circle_count--;
}

void free_all_circle(void)
{
    for (int i = 0; i < circle_count; i++)
        free(circles[i]);
    circle_count = 0;
}

void write_svg_circle(FILE *f)
{
    for (int i = 0; i < circle_count; i++)
        fprintf(f, "  <circle cx=\"%g\" cy=\"%g\" r=\"%g\" fill=\"%s\" stroke=\"black\"/>\n",
                circles[i]->x, circles[i]->y, circles[i]->radius,
                PALETTE[circles[i]->couleur].svg);
}
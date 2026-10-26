#include <stdio.h>
#include <stdlib.h>
#include "ellipse.h"
#include "colors.h"

#define MAX_ELLIPSE 100

static Ellipse *ellipses[MAX_ELLIPSE];
static int ellipse_count = 0;

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

static Ellipse *create_ellipse(double x, double y, double radius_x, double radius_y, int couleur)
{
    Ellipse *ellipse = malloc(sizeof(Ellipse));
    if (ellipse == NULL)
        return NULL;

    ellipse->x = x;
    ellipse->y = y;
    ellipse->radius_x = radius_x;
    ellipse->radius_y = radius_y;
    ellipse->couleur = couleur;
    return ellipse;
}

static void print_one_ellipse(const Ellipse *ellipse)
{
    printf("%sEllipse (X = %lf, Y = %lf, Rayon X = %lf, Rayon Y = %lf) [%s]\n" RESET,
           PALETTE[ellipse->couleur].ansi,
           ellipse->x, ellipse->y, ellipse->radius_x, ellipse->radius_y,
           PALETTE[ellipse->couleur].nom);
}

void ask_for_ellipse(void)
{
    if (ellipse_count >= MAX_ELLIPSE)
    {
        printf(RED "Nombre maximum d'ellipses atteint\n" RESET);
        return;
    }

    printf(PURPLE);
    double x = read_double("Sélectionner X : ");
    double y = read_double("Sélectionner Y : ");
    double radius_x = read_double("Sélectionner Rayon X : ");
    double radius_y = read_double("Sélectionner Rayon Y : ");
    printf(RESET);

    int couleur = choisir_couleur();

    Ellipse *ellipse = create_ellipse(x, y, radius_x, radius_y, couleur);
    if (ellipse == NULL)
    {
        printf(RED "Erreur d'allocation mémoire\n" RESET);
        return;
    }

    ellipses[ellipse_count++] = ellipse;
}

void print_ellipse(void)
{
    if (ellipse_count == 0)
    {
        printf(RED "Aucune ellipse à afficher\n" RESET);
        return;
    }
    for (int i = 0; i < ellipse_count; i++)
    {
        printf("[%d] ", i + 1);
        print_one_ellipse(ellipses[i]);
    }
}

static int select_ellipse(void)
{
    if (ellipse_count == 0)
    {
        printf(RED "Aucune ellipse disponible\n" RESET);
        return -1;
    }
    print_ellipse();
    printf(PURPLE);
    int n = read_int("Numéro de l'ellipse : ");
    printf(RESET);

    if (n < 1 || n > ellipse_count)
    {
        printf(RED "Numéro invalide\n" RESET);
        return -1;
    }
    return n - 1;
}

void modify_ellipse(void)
{
    int index = select_ellipse();
    if (index < 0)
        return;

    Ellipse *ellipse = ellipses[index];

    int choice;
    do
    {
        printf(PURPLE "\nQue souhaitez-vous modifier ?\n"
                      "\t1. X\n\t2. Y\n\t3. Rayon X\n\t4. Rayon Y\n\t5. Couleur\n\t0. Sortir\n");
        choice = read_int("\tChoix : ");
        printf(RESET);

        switch (choice)
        {
        case 1:
            ellipse->x = read_double("Nouveau X : ");
            break;
        case 2:
            ellipse->y = read_double("Nouveau Y : ");
            break;
        case 3:
            ellipse->radius_x = read_double("Nouveau rayon X : ");
            break;
        case 4:
            ellipse->radius_y = read_double("Nouveau rayon Y : ");
            break;
        case 5:
            ellipse->couleur = choisir_couleur();
            break;
        case 0:
            break;
        default:
            printf(RED "Choix invalide, veuillez réessayer\n" RESET);
            break;
        }
    } while (choice != 0);
}

void delete_ellipse(void)
{
    int index = select_ellipse();
    if (index < 0)
        return;

    free(ellipses[index]);

    for (int i = index; i < ellipse_count - 1; i++)
        ellipses[i] = ellipses[i + 1];

    ellipse_count--;
}

void free_all_ellipse(void)
{
    for (int i = 0; i < ellipse_count; i++)
        free(ellipses[i]);
    ellipse_count = 0;
}

void write_svg_ellipse(FILE *f)
{
    for (int i = 0; i < ellipse_count; i++)
        fprintf(f, "  <ellipse cx=\"%g\" cy=\"%g\" rx=\"%g\" ry=\"%g\" fill=\"%s\" stroke=\"black\"/>\n",
                ellipses[i]->x, ellipses[i]->y, ellipses[i]->radius_x, ellipses[i]->radius_y,
                PALETTE[ellipses[i]->couleur].svg);
}
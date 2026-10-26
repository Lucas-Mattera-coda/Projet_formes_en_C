#include <stdio.h>
#include <stdlib.h>
#include "rectangle.h"
#include "colors.h"

#define MAX_RECTANGLE 100

static Rectangle *rectangles[MAX_RECTANGLE];
static int rectangle_count = 0;

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

static Rectangle *create_rectangle(double x, double y, double width, double height, int couleur)
{
    Rectangle *rectangle = malloc(sizeof(Rectangle));
    if (rectangle == NULL)
        return NULL;

    rectangle->x = x;
    rectangle->y = y;
    rectangle->width = width;
    rectangle->height = height;
    rectangle->couleur = couleur;
    return rectangle;
}

static void print_one_rectangle(const Rectangle *rectangle)
{
    printf("%sRectangle (X = %lf, Y = %lf, Largeur = %lf, Hauteur = %lf) [%s]\n" RESET,
           PALETTE[rectangle->couleur].ansi,
           rectangle->x, rectangle->y, rectangle->width, rectangle->height,
           PALETTE[rectangle->couleur].nom);
}

void ask_for_rectangle(void)
{
    if (rectangle_count >= MAX_RECTANGLE)
    {
        printf(RED "Nombre maximum de rectangles atteint\n" RESET);
        return;
    }

    printf(PURPLE);
    double x = read_double("Sélectionner X : ");
    double y = read_double("Sélectionner Y : ");
    double width = read_double("Sélectionner Largeur : ");
    double height = read_double("Sélectionner Hauteur : ");
    printf(RESET);

    int couleur = choisir_couleur();

    Rectangle *rectangle = create_rectangle(x, y, width, height, couleur);
    if (rectangle == NULL)
    {
        printf(RED "Erreur d'allocation mémoire\n" RESET);
        return;
    }

    rectangles[rectangle_count++] = rectangle;
}

void print_rectangle(void)
{
    if (rectangle_count == 0)
    {
        printf(RED "Aucun rectangle à afficher\n" RESET);
        return;
    }
    for (int i = 0; i < rectangle_count; i++)
    {
        printf("[%d] ", i + 1);
        print_one_rectangle(rectangles[i]);
    }
}

static int select_rectangle(void)
{
    if (rectangle_count == 0)
    {
        printf(RED "Aucun rectangle disponible\n" RESET);
        return -1;
    }
    print_rectangle();
    printf(PURPLE);
    int n = read_int("Numéro du rectangle : ");
    printf(RESET);

    if (n < 1 || n > rectangle_count)
    {
        printf(RED "Numéro invalide\n" RESET);
        return -1;
    }
    return n - 1;
}

void modify_rectangle(void)
{
    int index = select_rectangle();
    if (index < 0)
        return;

    Rectangle *rectangle = rectangles[index];

    int choice;
    do
    {
        printf(PURPLE "\nQue souhaitez-vous modifier ?\n"
                      "\t1. X\n\t2. Y\n\t3. Largeur\n\t4. Hauteur\n\t5. Couleur\n\t0. Sortir\n");
        choice = read_int("\tChoix : ");
        printf(RESET);

        switch (choice)
        {
        case 1:
            rectangle->x = read_double("Nouveau X : ");
            break;
        case 2:
            rectangle->y = read_double("Nouveau Y : ");
            break;
        case 3:
            rectangle->width = read_double("Nouvelle largeur : ");
            break;
        case 4:
            rectangle->height = read_double("Nouvelle hauteur : ");
            break;
        case 5:
            rectangle->couleur = choisir_couleur();
            break;
        case 0:
            break;
        default:
            printf(RED "Choix invalide, veuillez réessayer\n" RESET);
            break;
        }
    } while (choice != 0);
}

void delete_rectangle(void)
{
    int index = select_rectangle();
    if (index < 0)
        return;

    free(rectangles[index]);

    for (int i = index; i < rectangle_count - 1; i++)
        rectangles[i] = rectangles[i + 1];

    rectangle_count--;
}

void free_all_rectangle(void)
{
    for (int i = 0; i < rectangle_count; i++)
        free(rectangles[i]);
    rectangle_count = 0;
}

void write_svg_rectangle(FILE *f)
{
    for (int i = 0; i < rectangle_count; i++)
        fprintf(f, "  <rect x=\"%g\" y=\"%g\" width=\"%g\" height=\"%g\" fill=\"%s\" stroke=\"black\"/>\n",
                rectangles[i]->x, rectangles[i]->y, rectangles[i]->width, rectangles[i]->height,
                PALETTE[rectangles[i]->couleur].svg);
}
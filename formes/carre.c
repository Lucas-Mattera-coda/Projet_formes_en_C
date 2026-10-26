#include <stdio.h>
#include <stdlib.h>
#include "carre.h"
#include "colors.h"

#define MAX_SQUARE 100

static Square *squares[MAX_SQUARE];
static int square_count = 0;

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

static Square *create_square(double x, double y, double side, int couleur)
{
    Square *square = malloc(sizeof(Square));
    if (square == NULL)
        return NULL;

    square->x = x;
    square->y = y;
    square->side = side;
    square->couleur = couleur;
    return square;
}

static void print_one_square(const Square *square)
{
    printf("%sCarré (X = %lf, Y = %lf, Côté = %lf) [%s]\n" RESET,
           PALETTE[square->couleur].ansi,
           square->x, square->y, square->side,
           PALETTE[square->couleur].nom);
}

void ask_for_square(void)
{
    if (square_count >= MAX_SQUARE)
    {
        printf(RED "Nombre maximum de carrés atteint\n" RESET);
        return;
    }

    printf(PURPLE);
    double x = read_double("Sélectionner X : ");
    double y = read_double("Sélectionner Y : ");
    double side = read_double("Sélectionner Côté : ");
    printf(RESET);

    int couleur = choisir_couleur();

    Square *square = create_square(x, y, side, couleur);
    if (square == NULL)
    {
        printf(RED "Erreur d'allocation mémoire\n" RESET);
        return;
    }

    squares[square_count++] = square;
}

void print_square(void)
{
    if (square_count == 0)
    {
        printf(RED "Aucun carré à afficher\n" RESET);
        return;
    }
    for (int i = 0; i < square_count; i++)
    {
        printf("[%d] ", i + 1);
        print_one_square(squares[i]);
    }
}

static int select_square(void)
{
    if (square_count == 0)
    {
        printf(RED "Aucun carré disponible\n" RESET);
        return -1;
    }
    print_square();
    printf(PURPLE);
    int n = read_int("Numéro du carré : ");
    printf(RESET);

    if (n < 1 || n > square_count)
    {
        printf(RED "Numéro invalide\n" RESET);
        return -1;
    }
    return n - 1;
}

void modify_square(void)
{
    int index = select_square();
    if (index < 0)
        return;

    Square *square = squares[index];

    int choice;
    do
    {
        printf(PURPLE "\nQue souhaitez-vous modifier ?\n"
                      "\t1. X\n\t2. Y\n\t3. Côté\n\t4. Couleur\n\t0. Sortir\n");
        choice = read_int("\tChoix : ");
        printf(RESET);

        switch (choice)
        {
        case 1:
            square->x = read_double("Nouveau X : ");
            break;
        case 2:
            square->y = read_double("Nouveau Y : ");
            break;
        case 3:
            square->side = read_double("Nouveau côté : ");
            break;
        case 4:
            square->couleur = choisir_couleur();
            break;
        case 0:
            break;
        default:
            printf(RED "Choix invalide, veuillez réessayer\n" RESET);
            break;
        }
    } while (choice != 0);
}

void delete_square(void)
{
    int index = select_square();
    if (index < 0)
        return;

    free(squares[index]);

    for (int i = index; i < square_count - 1; i++)
        squares[i] = squares[i + 1];

    square_count--;
}

void free_all_square(void)
{
    for (int i = 0; i < square_count; i++)
        free(squares[i]);
    square_count = 0;
}

void write_svg_square(FILE *f)
{
    for (int i = 0; i < square_count; i++)
        fprintf(f, "  <rect x=\"%g\" y=\"%g\" width=\"%g\" height=\"%g\" fill=\"%s\" stroke=\"black\"/>\n",
                squares[i]->x, squares[i]->y, squares[i]->side, squares[i]->side,
                PALETTE[squares[i]->couleur].svg);
}
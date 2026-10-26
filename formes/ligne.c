#include <stdio.h>
#include <stdlib.h>
#include "ligne.h"
#include "colors.h"

#define MAX_LINES 100

static Line *lines[MAX_LINES];

static int line_count = 0;

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

static Line *create_line(double x1, double y1, double x2, double y2, int couleur)
{
    Line *line = malloc(sizeof(Line));

    if (line == NULL)
        return NULL;

    line->x1 = x1;
    line->y1 = y1;
    line->x2 = x2;
    line->y2 = y2;
    line->couleur = couleur;
    return line;
}

static void print_one_line(const Line *line)
{
    printf("%sLIGNE (X1 = %lf, Y1 = %lf, X2 = %lf, Y2 = %lf) [%s]\n" RESET,
           PALETTE[line->couleur].ansi,
           line->x1, line->y1, line->x2, line->y2,
           PALETTE[line->couleur].nom);
}

void ask_for_line(void)
{
    if (line_count >= MAX_LINES)
    {
        printf(RED "Nombre maximum de lignes atteint\n" RESET);
        return;
    }

    printf(PURPLE);
    double x1 = read_double("Sélectionner X1 : ");
    double y1 = read_double("Sélectionner Y1 : ");
    double x2 = read_double("Sélectionner X2 : ");
    double y2 = read_double("Sélectionner Y2 : ");
    printf(RESET);

    int couleur = choisir_couleur();

    Line *line = create_line(x1, y1, x2, y2, couleur);
    if (line == NULL)
    {
        printf(RED "Erreur d'allocation mémoire\n" RESET);
        return;
    }

    lines[line_count++] = line;
}

void print_line(void)
{
    if (line_count == 0)
    {
        printf(RED "Aucune ligne à afficher\n" RESET);
        return;
    }
    for (int i = 0; i < line_count; i++)
    {
        printf("[%d] ", i + 1);
        print_one_line(lines[i]);
    }
}

static int select_line(void)
{
    if (line_count == 0)
    {
        printf(RED "Aucune ligne disponible\n" RESET);
        return -1;
    }
    print_line();
    printf(PURPLE);
    int n = read_int("Numéro de la ligne : ");
    printf(RESET);

    if (n < 1 || n > line_count)
    {
        printf(RED "Numéro invalide\n" RESET);
        return -1;
    }
    return n - 1;
}

void modify_line(void)
{
    int index = select_line();
    if (index < 0)
        return;

    Line *line = lines[index];

    int choice;
    do
    {
        printf(PURPLE "\nQue souhaitez-vous modifier ?\n"
                      "\t1. X1\n\t2. Y1\n\t3. X2\n\t4. Y2\n\t5. Couleur\n\t0. Sortir\n");
        choice = read_int("\tChoix : ");
        printf(RESET);

        switch (choice)
        {
        case 1:
            line->x1 = read_double("Nouveau X1 : ");
            break;
        case 2:
            line->y1 = read_double("Nouveau Y1 : ");
            break;
        case 3:
            line->x2 = read_double("Nouveau X2 : ");
            break;
        case 4:
            line->y2 = read_double("Nouveau Y2 : ");
            break;
        case 5:
            line->couleur = choisir_couleur();
            break;
        case 0:
            break;
        default:
            printf(RED "Choix invalide, veuillez réessayer\n" RESET);
            break;
        }
    } while (choice != 0);
}

void delete_line(void)
{
    int index = select_line();
    if (index < 0)
        return;

    free(lines[index]);

    for (int i = index; i < line_count - 1; i++)
        lines[i] = lines[i + 1];

    line_count--;
}

void free_all_lines(void)
{
    for (int i = 0; i < line_count; i++)
        free(lines[i]);
    line_count = 0;
}

void write_svg_line(FILE *f)
{
    for (int i = 0; i < line_count; i++)
        fprintf(f, "  <line x1=\"%g\" y1=\"%g\" x2=\"%g\" y2=\"%g\" stroke=\"%s\" stroke-width=\"3\"/>\n",
                lines[i]->x1, lines[i]->y1, lines[i]->x2, lines[i]->y2,
                PALETTE[lines[i]->couleur].svg);
}
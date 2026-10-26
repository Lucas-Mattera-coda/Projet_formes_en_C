#include <stdio.h>
#include "utils.h"
#include "colors.h"

static void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int read_int(const char *prompt)
{
    int v;
    printf("%s", prompt);
    while (scanf("%d", &v) != 1)
    {
        clear_input();
        printf(RED "Valeur invalide, réessayez : " PURPLE);
    }
    clear_input();
    return v;
}
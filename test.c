#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool est_vide(const char *chaine) {
    return chaine[0] == '\0';
}

int main() {
    char *chaine1 = strdup(""); // Chaîne vide
    char *chaine2 = NULL; // Chaîne non vide

    if (chaine1) {
        printf("La chaine 1 n'est pas vide.\n");
    } else {
        printf("La chaine 1 est vide.\n");
    }

    if (chaine2) {
        printf("La chaine 2 n'est pas vide.\n");
    } else {
        printf("La chaine 2 est vide.\n");
    }

    return 0;
}

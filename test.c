#include <stdio.h>
#include <stdlib.h>

typedef struct s_env
{
    int nombre;
    struct s_env *next;
} t_env;

// Fonction pour insérer un élément dans la liste triée
void inserer_tri(t_env **tete, t_env *nouveau) {
    t_env *courant;
    
    // Si la liste est vide ou si le nouvel élément est inférieur à la tête
    if (*tete == NULL || (*tete)->nombre >= nouveau->nombre) {
        nouveau->next = *tete;
        *tete = nouveau;
    } else {
        // Trouver l'endroit où insérer le nouvel élément
        courant = *tete;
        while (courant->next != NULL && courant->next->nombre < nouveau->nombre) {
            courant = courant->next;
        }
        nouveau->next = courant->next;
        courant->next = nouveau;
    }
}

// Fonction pour trier la liste chaînée
void trier_liste(t_env **tete) {
    t_env *nouveau_tete = NULL; // Liste triée
    
    t_env *courant = *tete;
    while (courant != NULL) {
        t_env *suivant = courant->next;
        inserer_tri(&nouveau_tete, courant);
        courant = suivant;
    }
    
    *tete = nouveau_tete; // Mettre à jour la tête de la liste
}

// Fonction pour ajouter un élément à la liste
void ajouter_element(t_env **tete, int nombre) {
    t_env *nouveau = malloc(sizeof(t_env));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire.\n");
        exit(EXIT_FAILURE);
    }
    nouveau->nombre = nombre;
    nouveau->next = NULL;

    if (*tete == NULL) {
        *tete = nouveau;
    } else {
        t_env *courant = *tete;
        while (courant->next != NULL) {
            courant = courant->next;
        }
        courant->next = nouveau;
    }
}

// Fonction pour afficher la liste chaînée
void afficher_liste(t_env *tete) {
    printf("Liste triee :\n");
    t_env *courant = tete;
    while (courant != NULL) {
        printf("%d ", courant->nombre);
        courant = courant->next;
    }
    printf("\n");
}

int main() {
    t_env *tete = NULL; // Initialiser la liste

    // Ajouter des éléments à la liste
    ajouter_element(&tete, 5);
    ajouter_element(&tete, 3);
    ajouter_element(&tete, 8);
    ajouter_element(&tete, 1);
    ajouter_element(&tete, 9);
    ajouter_element(&tete, 6);
    ajouter_element(&tete, 2);
    ajouter_element(&tete, 4);
    ajouter_element(&tete, 7);

    // Trier la liste
    trier_liste(&tete);

    // Afficher la liste triée
    afficher_liste(tete);

    return 0;
}

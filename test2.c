#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

void modify_environment(const char *name, const char *value) {
    // Recherche de la variable d'environnement existante
    int index = -1;
    for (int i = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], name, strlen(name)) == 0 &&
            environ[i][strlen(name)] == '=') {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // La variable d'environnement existe, la modifie
        char *new_entry = (char *)malloc(strlen(name) + strlen(value) + 2);
        sprintf(new_entry, "%s=%s", name, value);
        environ[index] = new_entry;
    } else {
        // La variable d'environnement n'existe pas, l'ajoute
        int num_env_vars = 0;
        while (environ[num_env_vars] != NULL) {
            num_env_vars++;
        }
        char **new_environ = (char **)malloc((num_env_vars + 2) * sizeof(char *));
        for (int i = 0; i < num_env_vars; i++) {
            new_environ[i] = environ[i];
        }
        char *new_entry = (char *)malloc(strlen(name) + strlen(value) + 2);
        sprintf(new_entry, "%s=%s", name, value);
        new_environ[num_env_vars] = new_entry;
        new_environ[num_env_vars + 1] = NULL;
        environ = new_environ;
    }
}

int main() {
    // Affiche les variables d'environnement actuelles
    printf("Environnement actuel :\n");
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    // Modifie la variable d'environnement "TEST" à "123"
    modify_environment("TEST", "123");

    // Affiche les variables d'environnement après modification
    printf("\nEnvironnement après modification :\n");
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    return 0;
}

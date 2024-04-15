#include <stdio.h>
#include "include/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char* input;

	char *tout_casser;
	tout_casser = malloc(52 * sizeof(t_env));
	char *redit;
	int i = 100;
	while (--i)
		redit = strdup("1000000000000000000");
    while ((input = readline("minishell > ")) != NULL) {
		add_history(input);

        printf("Vous avez saisi : %s\n", input);
        free(input);
    }

    return 0;   
}

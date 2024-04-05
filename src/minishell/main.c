#include "minishell.h"

void	ft_env(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n",env->cle, env->params);
		env = env->next;
	}
}

int main(int ac, char **av, char **envp)
{
	char *prompt;
	(void)ac;
	(void)av;
	t_env *env = NULL;
	env = init_env(envp);
	if (env == NULL)
		return (printf("Erreur malloc\n"), 2);
	while (1)
	{
		prompt = readline("> ");
		if (ft_strncmp(prompt, "env", 4) == 0)
			ft_env(env);
		if (ft_strncmp(prompt, "unset", 5) == 0)
			ft_unset(env, prompt);
		printf("%s, readline\n", prompt);
	}
	return (0);
}
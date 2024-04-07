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
		if (!prompt)
			return (999); // le dernier exit status
		else if (ft_strncmp(prompt, "env", 3) == 0)
			ft_env(env);
		else if (ft_strncmp(prompt, "unset", 5) == 0)
		{
			char **unset_value = ft_split(prompt + 5, ' '); 
			ft_unset(&env, unset_value);
		}
		else if (ft_strncmp(prompt, "echo", 4) == 0)
		{
			char **echo_value = ft_split(prompt + 4, ' ');	
			ft_echo(env, echo_value);
		}
		else if (ft_strncmp(prompt, "export", 6) == 0)
		{
			char **export_value = ft_split(prompt + 6, ' ');	
			ft_export(&env, export_value);
		}
		else if (ft_strncmp(prompt, "pwd", 3) == 0)	
			ft_pwd();
		printf("prompt %s, readline\n", prompt);
	}
	return (0);
}
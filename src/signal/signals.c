#include "minishell.h"

void c_new_prompt(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}
void	c_quite_exec(int signal)
{
	if (signal == SIGINT)
		printf("\n");
	return ;
}

void	d_quite(int signal)
{
	if (signal == SIGQUIT)
		exit (0);
	return ;
}

void	slash_dump(int signal)
{
	int *i = NULL;
	if (signal == SIGQUIT)
		printf("%d", *i);
	return ;
}

void	slash_exec(int signal)
{
	if (signal == SIGQUIT)
		return ;
	return ;
}




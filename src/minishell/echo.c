#include "minishell.h"

static void print_echo(char **str)
{
	int	i;

	i = -1;
	while(str[++i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
	}
}

void	ft_echo(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(str[i], "-n", 2) == 0)
	{
		print_echo(&str[i + 1]);
		return ;
	}
	print_echo(str);
	printf("\n");
}

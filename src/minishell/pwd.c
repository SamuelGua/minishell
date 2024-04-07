#include "minishell.h"

void	ft_pwd(void)
{
	char *path_name;

	path_name = getcwd(NULL, 0);
	if (!path_name)
	{
		printf("Error malloc\n");
		return ;
	}
	printf("%s\n", path_name);
}
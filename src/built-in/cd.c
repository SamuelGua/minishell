#include "minishell.h"

char *absolut_path()
{
	char	*path_name;
	char	*absolute;

	path_name = getcwd(NULL, 0);
	if (!path_name)
	{
		printf("Error malloc\n");
		return (NULL);
	}
	absolute = ft_strjoin(path_name, "/");
	free(path_name);
	return (absolute);
}
// char *is_relative(char *absolut, char *str)
// {
// }

//getenv
int	cd_home(t_env *env)
{
	while (env && ft_strncmp(env->cle, "HOME", 5) != 0)
		env = env->next;
	if (!env)
		return(printf("bash: cd: « HOME » non défini [a mettre en anglais]\n"));
	printf("%s\n",env->params);
	if (chdir(env->params))
		perror("bash: cd [a corriger]");
	return 0;

}

void	ft_cd(t_env *env, char **str)
{
	int		i;
	char	*path;

	i = 0;
	if (!str)
	{
		cd_home(env);
		return ;
	}
	while (str[i])
		i++;
	if (i > 1)
	{
		printf("bash: cd: trop d'arguments [a mettre en anglais]\n");	
		return ; 
	}
	path = absolut_path();
	if (!path)
		return ;
	// creer une fonction free_strjoin
	// *******************************
	path = ft_strjoin(path, str[0]);
	// *******************************
	if (chdir(path))
		perror("bash: cd [a corriger]");
	free(path);
}

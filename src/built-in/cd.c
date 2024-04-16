#include "minishell.h"

//getenv
// modifier les environements
int	cd_home(t_env *env)
{
	while (env && ft_strncmp(env->cle, "HOME", 5) != 0)
		env = env->next;
	if (!env)
		return(printf("bash: cd: HOME not set\n"));
	printf("%s\n",env->params);
	if (chdir(env->params))
		perror("bash: cd");
	return 0;

}

void	ft_cd(t_env *env, char **str)
{
	int		i;

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
		printf("bash: cd: too many arguments\n");	
		return ; 
	}
	if (chdir(*str))
		perror("bash: cd");
	ft_free(str);
}

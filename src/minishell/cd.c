#include "minishell.h"

static void pwd_update(t_env *env, char *directory)
{
	t_env *pwd = NULL;
	t_env *oldpwd = NULL;
	
	while ()
}

static int home_set(t_env *env)
{
	while (env && ft_strncmp(env->cle, "HOME", 5) != 0)
		env = env->next;
	if (!env)
		return (printf("bash: cd: « HOME » is not set\n") , 1);
	else if (chdir(env->params))
		return (printf("bash: cd: %s: Aucun fichier ou dossier de ce nom\n",
			env->cle) , 1);
	return (0);
}


void ft_cd(t_env *env, char *directory)
{
	if (!directory)
	{
		char *path_name;

		path_name = getcwd(NULL, 0);
		if (!path_name)
		{
			printf("Error malloc\n");
			return ;
		}
		home_set(env);
		return ;
	}
	if
	{
		
	}
}
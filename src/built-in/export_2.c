#include "minishell.h"

void	free_export(t_export *export)
{
	if (export)
	{
		free_export(export->left);
		free_export(export->right);
		free(export->cle);
		free(export->params);
		free(export);
	}
}

static t_export *ft_lstnew_export(char *cle, char *params)
{
	t_export	*new;

	new = malloc(sizeof(t_export));
	new->cle = ft_strdup(cle);
	if(!new->cle)
		return (free(new), NULL);
	new->params = ft_strdup(params);
	if (!new->params)
		return (free(new->cle), free(new), NULL);
	new->left = NULL;
	new->right = NULL;
	return (new);
}
static void	insert_export(t_export **list, t_export *node)
{
	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	if (ft_strncmp((*list)->cle, node->cle, 100) > 0)
		insert_export(&(*list)->left, node);
	else
		insert_export(&(*list)->right, node);
}

t_export *init_export(t_env *env)
{
	t_export *tmp;
	t_export *export;
	
	export = NULL;
	if (env == NULL)
		return (NULL);
	while (env)
	{
		tmp = ft_lstnew_export(env->cle, env->params);
		if (!tmp)
			return (free_export(export), NULL);
		insert_export(&export, tmp);
		env = env->next;
	}
	return (export);
}
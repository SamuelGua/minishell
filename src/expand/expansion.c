#include "minishell.h"

char *variables_expand(char *str, t_env *env, int i, int *last_exp, char *new)
{
	int len;

	len = 0;
	while (str[i + len] && str[i + len] != 32)
		len++;
	while (env && ft_strncmp(&str[i + 1], env->cle, len))
		env = env->next;
	if (env)
	{
		if (!new)
		{
			str[i] = '\0';
			new = ft_strdup(str);
			str[i] = '$';
			new = ft_free_strjoin(new, env->params);
		}
		else
		{
			new = ft_free_strjoin(new, &str[*last_exp]);
			new = ft_free_strjoin(new, env->params);
		}
	}
	else
	{
		if (!new)
		{
			str[i] = '\0';
			new = ft_strdup(str);
			str[i] = '$';
		}
		else
			new = ft_free_strjoin(new, &str[*last_exp]);

	}
	printf("str[%d] = %s\n", *last_exp, &str[*last_exp]);
	*last_exp = i + len + 1;
	return (new);
}

int	is_quoted(int quoted, char c)
{
	if (quoted == 0 && c == '\'')
		return (S_QUOTE);
	else if (quoted == 0 && c == '\"')
		return (D_QUOTE);
	else if (quoted == S_QUOTE && c == '\'')
		return (NO_QUOTE);
	else if (quoted == D_QUOTE && c == '\"')
		return (NO_QUOTE);
	return (quoted);
}

char *expansion(char *str, t_env *env)
{
	int i;
	int quoted;
	char *new;
	int l_expd;

	i = 0;
	l_expd = i;
	new =  NULL;
	quoted = NO_QUOTE;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		quoted = is_quoted(quoted, str[i]);
		if (str[i] == '$' && str[i + 1] != '\0' && str[i] != 32 && quoted != S_QUOTE)
		{
			new = variables_expand(str, env, i, &l_expd, new);
			i = l_expd;
		}
		else
			i++;
	}
	if (new)
		new = ft_free_strjoin(new, &str[l_expd]);
	else
		return (str);
	printf(" 1 - %s\n", new);
	return (new);
}

#include "minishell.h"

typedef struct s_expand
{
	int i;
	char *new;
	int l_exp;

}	t_exutils;

void add_expand(char *str, t_env *env, t_exutils *ex)
{
	int len;

	len = 0;
	while (str[ex->i + len + 1] && check_whitespace(str[ex->i + len + 1]) != 1
		&& str[ex->i + len + 1] != '\'' && str[ex->i + len + 1] != '\"' && str[ex->i + len + 1] != '$')
		len++;
	str[ex->i] = '\0';
	printf("len %i\n", len);
	ex->new = ft_free_strjoin(ex->new, &str[ex->l_exp]);
	while (env && (ft_strncmp(&str[ex->i + 1], env->cle, len) != 0 || len != (int)ft_strlen(env->cle)))
		env = env->next;
	if (env)
		ex->new = ft_free_strjoin(ex->new, env->params);
	str[ex->i] = '$';
	ex->l_exp = ex->i + len + 1;
	ex->i = ex->l_exp;
	printf("%s\n", &str[ex->i]);
}

void dollar_dollar(char *str, t_env *env, t_exutils *ex)
{
	char *sys;

	sys = "SYSTEMD_EXEC_PID";
	str[ex->i] = '\0';
	ex->new = ft_free_strjoin(ex->new, &str[ex->l_exp]);
	while (env && (ft_strncmp(sys, env->cle, 16) != 0 || 16 != (int)ft_strlen(env->cle)))
		env = env->next;
	if (env)
		ex->new = ft_free_strjoin(ex->new, env->params);
	str[ex->i] = '$';
	ex->l_exp = ex->i + 1 + 1;
	ex->i = ex->l_exp;
}

char	*expansion(char *str, t_env *env)
{
	t_exutils ex;
	ex.i = 0;
	ex.new = ft_calloc(1, 1);

	while (str[ex.i] && str[ex.i] != '$' &&check_whitespace(str[ex.i + 1]) == 0)
		ex.i++;
	if (str[ex.i] && str[ex.i] == '$')
	{
		str[ex.i] = '\0';
		ex.new = ft_strdup(str);
		str[ex.i] = '$';
	}
	while (str[ex.i] && check_whitespace(str[ex.i]))
		ex.i++;
	ex.l_exp = ex.i;
	while (str[ex.i])
	{
		if (str[ex.i] == '$' && str[ex.i + 1] == '$')
			dollar_dollar(str, env, &ex);
		else if (str[ex.i] == '$' && check_whitespace(str[ex.i + 1]) != 1 && str[ex.i + 1] != '\0')
			add_expand(str, env, &ex);
		else
			ex.i++;
	}
	if (ex.new[0])
	{
		ex.new = ft_free_strjoin(ex.new, &str[ex.l_exp]);
		return (ex.new);
	}
	free(ex.new);
	return (str);
}

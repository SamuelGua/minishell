#include "minishell.h"

int	is_quoted(int quoted, char c)
{
	if (quoted == NO_QUOTE && c == '\'')
		return (S_QUOTE);
	else if (quoted == NO_QUOTE && c == '\"')
		return (D_QUOTE);
	else if (quoted == S_QUOTE && c == '\'')
		return (NO_QUOTE);
	else if (quoted == D_QUOTE && c == '\"')
		return (NO_QUOTE);
	return (quoted);
}
char *clean_quote(char *str)
{
	int		i;
	int		j;
	int		quoted;
	char	*new;

	i = 0;
	j = 0;
	quoted = NO_QUOTE;
	new = malloc(sizeof(str) + 1);
	if (!new)
		return (NULL);
	while(str[i])
	{
		quoted = is_quoted(quoted, str[i]);
		printf("c = %c \t| quoted = %d\n", str[i], quoted);
		if ((quoted == NO_QUOTE && (str[i] == '\'' || str[i] == '\"')))
		{
			i++;
		}
		else
		{
			new[j] = str[i];
			(j++, i++);
		}			
	}
	(free(str), new[j] = '\0');
	return (new);
}

char	*delete_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (clean_quote(str));
		i++;
	}
	return (str);
}

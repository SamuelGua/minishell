#include <stdio.h>
#include <stdlib.h>

typedef struct s_env
{
	int				cle;
	struct s_env	*droite;
	struct s_env	*gauche;
}	t_env;

t_env	*ft_lstnew(int content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->cle = content;
	new->droite = NULL;
	new->gauche = NULL;
	return (new);
}

void	insert(t_env **list, t_env *node)
{
	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	if ((*list)->cle > node->cle)
		insert(&(*list)->gauche, node);
	else
		insert(&(*list)->droite, node);
}

void	print_list(t_env *list)
{
	if (list == NULL)
		return ;
	if (list->gauche != NULL)
		print_list(list->gauche);
	printf("Node : %d\n", list->cle);
	if (list->droite != NULL)
		print_list(list->droite);
}

int main()
{
	int tab[] = {10 , 5 , 15, 45, 100, 1, 6, 23};
	t_env *list = NULL;
	t_env *node = NULL;
	t_env *tmp = NULL;
	t_env *tmp2 = NULL;
	int i = 0;
	int len = sizeof(tab) / sizeof(int);

	while (i < len)
	{
		node = ft_lstnew(tab[i]);
		insert(&list, node);
		i++;
	}
	print_list(list);
	// head = list;
	// i++;
	// while (i < len)
	// {
	// 	list = head;
	// 	tmp = ft_lstnew(tab[i]);
	// 	while (list)
	// 	{
	// 		if (list->cle < tab[i])
	// 			list = list->droite;
	// 		else if (list->cle > tab[i])
	// 			list = list->gauche;
	// 		if (list)
	// 			tmp2 = list;
	// 	}
	// 	if (tmp2->cle < tab[i])
	// 		tmp2->droite = tmp;
	// 	else if (tmp2->cle > tab[i])
	// 		tmp2->gauche = tmp;
	// 	i++;
	// }

}

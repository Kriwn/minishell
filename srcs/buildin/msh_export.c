/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:26:50 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/25 16:02:02 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*mymake_tuple(t_tuple *new_node, char *str, char c)
{
	size_t	i;
	size_t	n;
	char	*temp;

	dprintf(2,"str: %s\n", str);
	i = 0;
	while (str[i] != c)
		i++;
	temp = malloc(sizeof(char) * (i + 1));
	temp[0] = '\0';
	if (temp == NULL)
		return (NULL);
	new_node->key = temp;
	ft_strlcat(temp, str, i + 1);
	n = ft_strlen(str) - i;
	temp = malloc(sizeof(char) * (n + 1));
	if (temp == NULL)
		return (NULL);
	temp[0] = '\0';
	ft_strlcat(temp, (str + i + 1), n);
	new_node->value = temp;
	return ((void *)(1));
}

void	sort_env(t_tuple **env)
{
	t_tuple	*current;
	t_tuple	*next;
	char	*temp;

	current = *env;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcmp(current->key, next->key) > 0)
			{
				temp = current->key;
				current->key = next->key;
				next->key = temp;
				temp = current->value;
				current->value = next->value;
				next->value = temp;
			}
			next = next->next;
		}
		current = current->next;
	}
}

// make_tuple not work here
int	msh_export(t_p *list)
{
	t_tuple *new_node;
	t_tuple **data;

	if (list->args[1] == NULL)
		return (EXIT_FAILURE);
	data = &list->msh->tuple;
	new_node = malloc(sizeof(t_tuple));
	if (new_node == NULL || mymake_tuple(new_node, list->args[1], '=') == NULL)
		return (EXIT_FAILURE);
	new_node->next = NULL;
	if (!*data)
	{
		*data = new_node;
		(*data)->tail = new_node;
	}
	else
	{
		(*data)->tail->next = new_node;
		(*data)->tail = new_node;
	}
	return (EXIT_SUCCESS);
}

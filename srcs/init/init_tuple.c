/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tuple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:24:33 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/17 16:57:11 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*make_tuple(t_tuple *new_node, char *str, char c)
{
	size_t	i;
	size_t	n;
	char	*temp;

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

int	init_tuple(t_tuple **data, char **env)
{
	size_t	i;
	t_tuple	*new_node;
	char	**temp;

	i = 0;
	while (env[i])
	{
		new_node = malloc(sizeof(t_tuple) * 1);
		if (new_node == NULL || make_tuple(new_node, env[i], '=') == NULL)
			return (-1);
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
		i++;
	}
}

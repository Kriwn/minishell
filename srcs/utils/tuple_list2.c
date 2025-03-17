/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:25:05 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/17 17:31:28 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_head(t_tuple **data, t_tuple *cur)
{
	*data = cur->next;
	if (*data)
		(*data)->tail = cur->tail;
}

void	delete_node(t_tuple **data, t_tuple *cur, t_tuple *prev)
{
	prev->next = cur->next;
	if (cur->next == NULL)
		(*data)->tail = prev;
}

void	remove_tuple(t_tuple **data, char *key)
{
	t_tuple	*cur;
	t_tuple	*prev;

	cur = *data;
	prev = NULL;
	while (cur)
	{
		if (ft_strlen(key) == ft_strlen(cur->key) && \
			!ft_strncmp(cur->key, key, ft_strlen(key)))
		{
			if (prev == NULL)
				delete_head(data, cur);
			else
				delete_node(data, cur, prev);
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:51:08 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/16 19:31:48 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tuple(t_tuple *data)
{
	while (data != NULL)
	{
		ft_putstr_fd(data->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(data->value, 1);
		write(1, "\n", 1);
		data = data->next;
	}
}

char	*get_value_from_key(t_tuple *data, char *key)
{
	char	*value;

	value = NULL;
	while (data)
	{
		if (!ft_strncmp(data->key, key, ft_strlen(key)))
			value = data->value;
		data = data->next;
	}
	return (value);
}

void	updata_value_from_key(t_tuple *data, char *key, char *new_value)
{
	while (data)
	{
		if (!ft_strncmp(data->key, key, ft_strlen(key)))
		{
			free(data->value);
			data->value = new_value;
		}
		data = data->next;
	}
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
			if (prev == NULL) // Deleting head node
			{
				*data = cur->next;
				if (*data)
					(*data)->tail = cur->tail;
			}
			else
			{
				prev->next = cur->next;
				if (cur->next == NULL) // Updating tail
					(*data)->tail = prev;
			}
			free(cur->key);
			free(cur->value);
			free(cur);
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}


void	clear_tuple(t_tuple **data)
{
	t_tuple	*cur;
	t_tuple	*temp;

	cur = *data;
	while (cur)
	{
		temp = cur;
		cur = cur->next;
		if (temp->key)
			free(temp->key);
		if (temp->value)
			free(temp->value);
		if (temp)
			free(temp);
	}
	*data = NULL;
}

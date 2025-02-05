/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:51:08 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/28 02:51:16 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tuple(t_tuple *data)
{
	while (data != NULL)
	{
		// printf("Key is %s Value is %s\n",data->key,data->value);
		ft_putstr_fd(data->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(data->value, 1);
		write(1, "\n", 1);
		data = data->next;
	}
}

char	*get_value_from_key(t_tuple *data,char *key)
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
	t_tuple *cur;
	t_tuple	*temp;

	cur = *data;
	temp = NULL;
	while (cur)
	{
		if (ft_strlen(key) == ft_strlen(cur->key) && !ft_strncmp(cur->key, key, ft_strlen(key)))
		{
			dprintf(2,"Key is %s\n",cur->key);
			if (temp == NULL)
			{
				cur->next->tail = (*data)->tail;
				*data = cur->next;
			}
			else if (cur->next == NULL)
				(*data)->tail = temp;
			else
				temp->next = cur->next;
			free(cur->key);
			free(cur->value);
		}
		temp = *data;
		cur = cur->next;
	}
}

void	clear_tuple(t_tuple **data)
{
	t_tuple *cur;
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

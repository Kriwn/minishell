/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:51:08 by krwongwa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/17 17:25:04 by krwongwa         ###   ########.fr       */
=======
/*   Updated: 2025/03/17 17:22:28 by jikarunw         ###   ########.fr       */
>>>>>>> be651b9fb92fb812b11889e905b143f438d8d82e
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
			return ;
		}
		data = data->next;
	}
	if (new_value)
		free(new_value);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:51:08 by krwongwa          #+#    #+#             */
/*   Updated: 2024/07/04 15:38:20 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"


void	print_tuple(t_tuple *data)
{
	while (data != NULL)
	{
		dprintf(2, "%s=%s\n",data->key, data->value);
		data = data->next;
	}
}

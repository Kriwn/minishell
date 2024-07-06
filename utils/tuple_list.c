/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltuple_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:51:08 by krwongwa          #+#    #+#             */
/*   Updated: 2024/07/04 14:53:54 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	print_tuple(t_tuple *data)
{
	while (data != NULL)
	{
		dprintf(2, "Key is %s Value is %s\n");
		data = data->next;
	}
}

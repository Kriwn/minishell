/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:31:29 by krwongwa          #+#    #+#             */
/*   Updated: 2024/07/15 17:15:19 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_env *data)
{
	data->home_path = NULL;
	clear_tuple(&data->tuple);
	print_tuple(data->tuple);
}

void	ft_error(t_env *data,char *word)
{
	dprintf(2,"%s",word);
	ft_free(data);
	exit(1);
}

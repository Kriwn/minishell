/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:31:29 by krwongwa          #+#    #+#             */
/*   Updated: 2024/07/29 16:19:05 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_msh *data)
{
	data->home_path = NULL;
	clear_tuple(&data->tuple);
}

void	ft_error(t_msh *data, char *word)
{
	ft_putstr_fd(word, 2);
	ft_free(data);
	exit(EXIT_FAILURE);
}

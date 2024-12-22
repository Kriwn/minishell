/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:19:20 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/22 22:20:09 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_pipe(t_p **list)
{
	*list = malloc(sizeof(t_p));
	if (!*list)
		return -1;
	(*list)->process_pid = NULL;
	(*list)->path = NULL;
}

void	init_minishell(t_msh *data, char **env)
{
	data->tuple = NULL;
	data->env = env;
	data->token = NULL;
	data->list = NULL;
	data->ast = NULL;
	if (init_tuple(&data->tuple, env) == -1)
		ft_error(data, "malloc error\n");
	if (init_pipe(&data->list) == -1)
		ft_error(data, "malloc error\n");
	data->home_path = get_value_from_key(data->tuple, "HOME=");
	data->code = 0;
	data->count_pipe = 0;
}

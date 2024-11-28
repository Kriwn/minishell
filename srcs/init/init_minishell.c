/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:19:20 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/28 20:58:15 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_pipe(t_p **list)
{
	*list = malloc(sizeof(t_p));
	if (!*list)
		return -1;
	(*list)->process_pid = NULL;
	(*list)->env = NULL;
	(*list)->path = NULL;
}

void	init_minishell(t_msh *data, char **env)
{
	data->tuple = NULL;
	data->token = NULL;
	data->list = NULL;
	data->ast = NULL;
	if (init_tuple(&data->tuple, env) == -1)
		ft_error(data, "malloc error\n");
	if (init_pipe(&data->list) == -1)
		ft_error(data, "malloc error\n");
	data->home_path = get_value_from_key(data->tuple, "HOME=");
	data->code = 0;
	//passe init
}

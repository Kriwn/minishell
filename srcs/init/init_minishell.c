/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:19:20 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/12 19:42:37 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_p	*init_pipe(void)
{
	t_p	*list;

	list = malloc(sizeof(t_p));
	if (!list)
		return (NULL);
	list->process_pid = NULL;
	list->path = NULL;
	return (list);
}

void	init_minishell(t_msh *data, char **env)
{
	int	temp;

	temp = 1;
	data->tuple = NULL;
	data->env = env;
	data->token = NULL;
	data->list = NULL;
	data->ast = NULL;
	temp = init_tuple(data, env);
	if (!temp)
	{
		clear_tuple(&data->tuple);
		ft_error(data, "malloc error\n");
	}
	data->list = init_pipe();
	if (!data->list)
		ft_error(data, "malloc error\n");
	data->home_path = get_value_from_key(data->tuple, "HOME=");
	data->code = 0;
	data->count_pipe = 0;
}

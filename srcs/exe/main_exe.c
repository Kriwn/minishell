/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:03 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/21 15:28:50 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	init_pipe(t_p **temp, t_msh *msh)
{
	t_p		*list;
	int		i;

	i = 0;
	list = *temp;
	list->process_pid = malloc(sizeof(int) * (msh->token->count_pipe + 1));
	list->env = msh->env;
	list->path = ft_split(get_value_from_key(msh->tuple, "PATH="), ':');
	list->pipe[0] = -1;
	list->pipe[1] = -1;
	list->fd_in = -1;
	list->fd_out = -1;
	while (i < msh->token->count_pipe)
	{
		list->process_pid[i] = 0;
		i++;
	}
}

int	main_exe(t_msh *msh)
{
	t_token	*curr;
	t_p		*list;

	curr = msh->token;
	list = msh->list;
	init_pipe(&list, msh);
	do_here_doc_task(curr, list);
	delete_token_heredoc(&msh->token);
	dprintf(2, "count pipe: %d\n", curr->count_pipe);
	if (curr->count_pipe == 0)
		return (exe_single_cmd(curr, list));
	return (pipe_task(curr, list));
}

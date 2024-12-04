/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:03 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/30 18:32:06 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	init_pipe(t_p **temp, t_msh *msh)
{
	printf("Ininit\n");
	t_p		*list;
	size_t	size;
	int		i;

	i = 0;
	list = *temp;
	size = msh->count_pipe + 1;
	list->process_pid = malloc(sizeof(int) * (size));
	list->env = msh->env;

	// printf("Before split token count pipe %d\n",msh->token->count_pipe);
	list->path = ft_split(get_value_from_key(msh->tuple, "PATH"), ':');
	// printf("After split token count pipe %d\n",msh->token->count_pipe);

	// for(int i = 0; list->path[i]; i++)
	// 	printf("%s\n",list->path[i]);

	list->pipe[0] = -1;
	list->pipe[1] = -1;
	list->fd_in = -1;
	list->fd_out = -1;
	while (i < size)
	{
		list->process_pid[i] = 0;
		i++;
	}
	printf("Outinit\n");
}

int	main_exe(t_msh *msh)
{
	t_p		*list;

	list = msh->list;
	printf("token count pipe %d\n",msh->token->count_pipe);
	init_pipe(&list,msh);
	do_here_doc_task(msh->ast, list);
	// delete_token_heredoc(&msh->token);
	if (msh->count_pipe == 0)
		return (exe_single_cmd(msh->ast, list));
	// return (pipe_task(ast, list));
}

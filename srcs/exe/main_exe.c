/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:03 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/13 13:20:15 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_all_process(t_p *list)
{
	size_t	i;
	int	status;

	i = 0;
	while (i < list->max)
	{
		if (list->process_pid[i] > -1)
			waitpid(list->process_pid[i], &status, WUNTRACED); // need to change status to list->code
		i++;
	}
	// freelist(list); need to do this
	printf("Eed All Process\n");
	return (WEXITSTATUS(status));
}


void	init_pipe(t_p **temp, t_msh *msh)
{
	t_p		*list;
	size_t	size;
	int		i;

	i = 0;
	list = *temp;
	size = msh->count_pipe + 1;
	list->process_pid = malloc(sizeof(int) * (size));
	list->iter = 0;
	list->path = ft_split(get_value_from_key(msh->tuple, "PATH"), ':');
	list->env = msh->env;
	list->code = &msh->code;
	list->max = 1; // need to chang to count pipe
	list->pipe[0] = -1;
	list->pipe[1] = -1;
	list->fd_in = -1;
	list->fd_out = -1;
	list->args = NULL;
	list->cmd = NULL;
	while (i < size)
	{
		list->process_pid[i] = 0;
		i++;
	}
}

// INDIRECT BROKEN
void	main_exe(t_msh *msh)
{
	t_p		*list;

	msh->count_pipe = 1;
	list = msh->list;
	// printf("token count pipe %d\n",msh->token->count_pipe);
	init_pipe(&list,msh);
	do_here_doc_task(msh->ast, list);
	if (msh->count_pipe == 0)
		exe_single_cmd(msh,msh->ast, list);
	else
	{
		pipe_task(msh->ast, list);
		msh->code = wait_all_process(list);
		// freelist()
	}

}

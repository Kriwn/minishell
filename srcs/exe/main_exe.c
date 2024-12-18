/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:03 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/18 22:36:55 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mode_signal_exe(int mode)
{
	if (mode == 0) // normal minishell mode
	{
		signal(SIGINT, &check_signal);
		signal(SIGQUIT, &check_signal);
	}
	else if (mode == 1) // parent
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2) // child
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}


void	wait_all_process(t_p *list)
{
	size_t	i;
	int	status;

	i = 0;
	while (i < list->max)
	{
		if (list->process_pid[i] > -1)
			waitpid(list->process_pid[i], &status, WUNTRACED);
		i++;
	}
	dprintf(2,"Eed All Process\n");
	*list->code = WEXITSTATUS(status);
}

void	init_pipe(t_p **temp, t_msh *msh)
{
	t_p		*list;
	int		i;

	i = 0;
	list = *temp;
	list->process_pid = malloc(sizeof(int) * (msh->count_pipe + 1));
	list->iter = 0;
	list->path = ft_split(get_value_from_key(msh->tuple, "PATH"), ':');
	list->env = msh->env;
	list->code = &msh->code;
	list->max = msh->count_pipe + 1;
	list->pipe[0] = -1;
	list->pipe[1] = -1;
	list->fd_in = -1;
	list->fd_out = -1;
	list->args = NULL;
	list->cmd = NULL;
	while (i < msh->count_pipe + 1)
	{
		list->process_pid[i] = 0;
		i++;
	}
}

// sleep command not work
void	main_exe(t_msh *msh)
{
	t_p		*list;

	dprintf(2,"Main Exe\n");
	msh->count_pipe = 0;
	list = msh->list;
	init_pipe(&list,msh);
	do_here_doc_task(msh->ast, list);
	if (msh->count_pipe == 0)
	{
		dprintf(2,"Single Command\n");
		mode_signal_exe(1);
		exe_single_cmd(msh,msh->ast, list);
	}
	else
	{
		mode_signal_exe(1);
		pipe_task(msh->ast, list);
	}
	wait_all_process(list);
	mode_signal_exe(0);
	free_list(list);
	dprintf(2,"EXITCODE %d\n",msh->code);
}

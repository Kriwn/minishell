/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:03 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/13 19:06:20 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mode_signal_exe(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, &check_signal);
		signal(SIGQUIT, &check_signal);
	}
	else if (mode == 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

/* segfault not work on some case
			// if (WIFSIGNALED(status))
			// {
			// 	signal = WTERMSIG(status);
			// 	if (signal == SIGSEGV)
			// 	{
			// 		*list->code = 128 + signal;
			// 		ft_puterrstr("Segmentation fault (core dumped)\n");
			// 	}
			// }
			// else
*/

void	wait_all_process(t_p *list)
{
	size_t	i;
	int		status;
	int		signal;

	i = 0;
	while (i < list->msh->count_pipe + 1)
	{
		if (list->process_pid[i] > -1)
		{
			waitpid(list->process_pid[i], &status, WUNTRACED);
			*list->code = WEXITSTATUS(status);
		}
		i++;
	}
}

void	init_pipe(t_p **temp, t_msh *msh)
{
	t_p	*list;
	int	i;

	i = 0;
	list = *temp;
	list->process_pid = malloc(sizeof(int) * (msh->count_pipe + 1));
	list->iter = 0;
	list->path = myft_split(get_value_from_key(msh->tuple, "PATH"), ':');
	list->env = msh->env;
	list->code = &msh->code;
	list->msh = msh;
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

void	main_exe(t_msh *msh)
{
	t_p	*list;
	int	a;
	int	b;

	a = -1;
	b = -1;
	list = msh->list;
	init_pipe(&list, msh);
	do_here_doc_task(msh->ast, list, &b);
	is_build_in_command(msh->ast, &a);
	if (msh->count_pipe == 0 && a == 0)
		exe_single_cmd(msh->ast, list);
	else if (b == 1)
	{
		mode_signal_exe(1);
		pipe_task(msh->ast, list);
		wait_all_process(list);
	}
	mode_signal_exe(0);
	free_list(list);
}

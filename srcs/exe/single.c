/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:49:36 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/18 22:16:38 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void setup_chile(t_p *list)
{
	if (list->fd_in > -1) // Set up input redirection
	{
		dup2(list->fd_in, 0);
		safe_close(list, 0);
	}
	if (list->fd_out > -1) // Set up output redirection
	{
		dup2(list->fd_out, 1);
		safe_close(list, 1);
	}
}
static void child_process(t_p *list)
{
	char *cmd_path;

	mode_signal_exe(2);
	cmd_path = find_path(list->cmd, list->path);
	setup_chile(list);	
	if (execve(cmd_path, list->args, list->env) == -1)
	{
		dprintf(2,"Errno is %d\n", errno);
		*list->code = ft_puterrorcmd(list->cmd, errno);
		if (cmd_path != NULL)
			free(cmd_path);
		exit(*list->code); // need to use this to exit child when error occur
	}
	if (cmd_path)
		free(cmd_path);
}

static void parent_process(t_p *list) // problem_here
{
	if (list->fd_in > -1)
		safe_close(list, 0);
	close(list->pipe[0]);
	close(list->pipe[1]);
	safe_close(list, 1);
}

// broken not give promt back
int run_single_cmd(t_p *list)
{
	char *cmd_path;

	list->process_pid[0] = fork();
	if (list->process_pid[0] == -1)
		return (perror("FORK : "), errno);
	if (list->process_pid[0] == 0)
		child_process(list);
	else
		parent_process(list);
}

int exe_single_cmd(t_msh *msh, t_ast *ast, t_p *list)
{
	int a;
	int status;

	a = -1;
	is_build_in_command(ast, &a);
	if (a == 1)
	{
		prepare_cmd(ast, list, &status); // check fd in this before run
		if (status == -1)
		{
			*list->code = 1;
			return 1;
		}
		run_single_cmd(list);
	}
	else
		printf("Build in command\n");
}

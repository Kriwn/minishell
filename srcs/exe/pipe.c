/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:28:33 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/23 20:35:29 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need to add run build in here;
void run_cmd(t_p *list,int status)
{
	char *cmd_path;

	cmd_path = find_path(list->cmd, list->path);
	dprintf(2,"CMD PATH is %s\n",cmd_path);
	dup2(list->fd_in, 0);
	safe_close(list, 0);
	if (status == -1)
	{
		*list->code = 1;
		exit(*list->code);
	}
	if (execve(cmd_path, list->args , list->env) == -1)
	{
		dprintf(2,"Errno is %d\n", errno);
		*list->code = ft_puterrorcmd(list->cmd, errno);
		if (cmd_path != NULL)
			free(cmd_path);
		exit(*list->code);
	}
	free(cmd_path);
}

void child_process(t_p *list, int status)
{
	int a;

	a = -1;
	mode_signal_exe(2);
	if (list->fd_out != -1)
	{
		dup2(list->fd_out, 1);
		close(list->pipe[0]);
		close(list->pipe[1]);
		safe_close(list, 1);
	}
	else
		pipe_write(list);
	check_build_in_command(list->cmd, &a);
	if (a == 0)
		dprintf(2,"RUN BUILD IN (PIPE)\n");
	else
		run_cmd(list,status);
}

void parent_process(t_p *list)
{
	if (list->fd_in > -1)
		safe_close(list, 0);
	list->fd_in = dup(list->pipe[0]);
	close(list->pipe[0]);
	close(list->pipe[1]);
}

void mutiple_exe(t_ast *ast, t_p *list)
{
	int status;

	status = 1;
	prepare_cmd(ast, list, &status); // check fd in this before run
	list->process_pid[list->iter] = fork();
	if (list->process_pid[list->iter] == -1)
	{
		perror("FORK : ");
		*list->code = errno;
	}
	if (list->process_pid[list->iter] == 0)
		child_process(list, status);
	else
		parent_process(list);
	clear_list(list);
	list->iter++;
}

void pipe_task(t_ast *ast, t_p *list)
{
	if (!ast)
		wait_all_process(list);

	if (ast->type == CMD_GROUP)
		mutiple_exe(ast, list);
	else if (ast->type == PIPE)
	{
		if (pipe(list->pipe) == -1)
		{
			perror("PIPE : ");
			*list->code = errno;
			return ;
		}
		pipe_task(ast->left, list);
		pipe_task(ast->right, list);
	}
}

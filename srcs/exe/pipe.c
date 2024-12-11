/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:28:33 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/09 17:24:06 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

run_cmd(t_p *list)
{
	char *cmd_path;

	cmd_path = find_path(list->cmd, list->path);
	if (execve(cmd_path, list->args, list->env) == -1)
	{
		*list->code = errno;
		free(cmd_path);
	}
	free(cmd_path);
}

void child_process(t_p *list)
{
	if (list->fd_out == 1)
		pipe_write(list);
	run_cmd(list);
}

void parent_process(t_p *list)
{
	close(list->pipe[1]);
	if (list->fd_in != -1)
		close(list->fd_in);
	list->fd_in = list->pipe[0];
}

void mutiple_exe(t_ast *ast, t_p *list)
{
	prepare_cmd(ast, list);
	if (pipe(list->pipe) == -1)
		printf("Error pipe\n");
	list->process_pid[list->iter] = fork();
	if (list->process_pid[list->iter] == 0)
		child_process(list);
	else
		parent_process(list);
	list->iter++;
}

int pipe_task(t_ast *ast, t_p *list)
{

	if (!ast)
		return;
	if (ast->type == CMD_GROUP)
		mutiple_exe(ast, list);
	else
	{
		pipe_task(ast->left, list);
		pipe_task(ast->right, list);
	}
}

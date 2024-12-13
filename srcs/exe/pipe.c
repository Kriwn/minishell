/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:28:33 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/13 13:16:27 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void run_cmd(t_p *list)
{
	char *cmd_path;

	cmd_path = find_path(list->cmd, list->path);
	dprintf(2, "CMD RUN IS %s\n", cmd_path);
	dup2(list->fd_in, 0);
	safe_close(list, 0);
	if (execve(cmd_path, list->args, list->env) == -1)
	{
		*list->code = errno; // need to do handle error pipe
		free(cmd_path);
	}
	free(cmd_path);
}

void child_process(t_p *list)
{
	if (list->fd_out != -1)
	{
		printf("FD OUT\n");
		dup2(list->fd_out, 1);
		close(list->pipe[0]);
		close(list->pipe[1]);
		safe_close(list, 1);
	}
	else
	{
		printf("PIPE WRITE\n");
		pipe_write(list);
	}
	run_cmd(list);
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
	printf("ITER%d\n", list->iter);
	prepare_cmd(ast, list);
	list->process_pid[list->iter] = fork();
	if (list->process_pid[list->iter] == -1)
		// ft_puterror("Fork error", errno, list);
		printf("Fork error\n");
	if (list->process_pid[list->iter] == 0)
		child_process(list);
	else
		parent_process(list);
	clear_list(list);
	list->iter++;
}

void pipe_task(t_ast *ast, t_p *list)
{
	if (!ast)
		return;

	if (ast->type == CMD_GROUP)
	{
		mutiple_exe(ast, list);
	}
	else if (ast->type == PIPE)
	{
		// Create a pipe
		if (pipe(list->pipe) == -1)
		{
			perror("Error creating pipe");
			return ;
		}
		pipe_task(ast->left, list);
		pipe_task(ast->right, list);
	}
}

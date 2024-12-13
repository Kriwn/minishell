/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:49:36 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/13 00:05:22 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_path(char *cmd, char **path)
{
	int i;
	char *temp;
	char *cmd_path;

	i = 0;
	if (find_slash(cmd))
		if (access(cmd, X_OK) == 0)
			return (cmd);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		// printf("Temp is %s\n",temp);
		cmd_path = ft_strjoin(temp, cmd);
		// printf("CMD_PATH is %s\n",cmd_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		//free(temp);// WTF Why I cannot free temp
		i++;
	}
	return NULL;
}

static void parent_process(t_p *list)
{
	safe_close(list, 0);
	safe_close(list, 1);
	if (list->pipe[0] > -1)
		close(list->pipe[0]);
	if (list->pipe[1] > -1)
		close(list->pipe[1]);
}

int run_single_cmd(t_p *list)
{
	char *cmd_path;

	list->process_pid[0] = fork();
	if (list->process_pid[0] == 0)
	{
		cmd_path = find_path(list->cmd, list->path);
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
		if (execve(cmd_path, list->args, list->env) == -1)
		{
			printf("Error exe\n");
			*list->code = errno; // need to do handle error pipe
			free(cmd_path);
			//free(list);
		}
		if (cmd_path)
			free(cmd_path);
	}
	else
		parent_process(list);
}

// only cat not use input to take and print output
int exe_single_cmd(t_msh *msh, t_ast *ast, t_p *list)
{
	int a;
	int status;

	a = -1;
	printf("Do single cmd\n");
	is_build_in_command(ast, &a);
	if (a == 1)
	{
		prepare_cmd(ast, list);
		run_single_cmd(list);
		waitpid(list->process_pid[0], &status, WUNTRACED);
		return (WEXITSTATUS(status));
	}
	else
		printf("Build in command\n");
}

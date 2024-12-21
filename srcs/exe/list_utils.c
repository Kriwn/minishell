/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:20:30 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/21 20:59:04 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clear_list(t_p *list)
{
	if (list->args)
		list->args = NULL;
	if (list->cmd)
		list->cmd = NULL;
}

void free2d(char **str)
{
	int i;

	if (!str)
	{
		dprintf(2,"No 2d array\n");
		return ;
	}
	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

void free_list(t_p *list)
{
	clear_list(list);
	free(list->process_pid);
	free2d(list->path);
	list->path = NULL;
	list->env = NULL;
	list->max = -1;
	close(list->pipe[0]);
	close(list->pipe[1]);
	list->pipe[0] = -1;
	list->pipe[1] = -1;
	safe_close(list, 0);
	safe_close(list, 1);
}

void prepare_cmd(t_ast *ast, t_p *list, int *status)
{
	if (!ast || *status == -1)
		return;
	if (ast->type == REDIRECT || ast->type == APPEND || ast->type == INDIRECT)
	{
		if (ast->type == REDIRECT)
			open_out_file(ast->right->args[0], list, 0, status);
			// list->fd_out = open(ast->right->args[0], O_RDWR | O_TRUNC | O_CREAT, 0644);
		else if (ast->type == APPEND)
			open_out_file(ast->right->args[0], list, 1, status);
			// list->fd_out = open(ast->right->args[0], O_RDWR | O_APPEND | O_CREAT, 0644);
		else if (ast->type == INDIRECT)
			open_in_file(ast->right->args[0], list,	status);
			// list->fd_in = open(ast->right->args[0], O_RDONLY);
	}
	if (ast->type == CMD)
	{
		if (list->cmd == NULL)
			list->cmd = ast->args[0];
		list->args = ast->args;

	}
	prepare_cmd(ast->left, list,status);
	prepare_cmd(ast->right, list,status);
}

void safe_close(t_p *list, int flag)
{
	if (flag == 0)
	{
		if (list->fd_in != -1)
		{
			close(list->fd_in);
			list->fd_in = -1;
		}
	}
	else
	{
		if (list->fd_out != -1)
		{
			close(list->fd_out);
			list->fd_out = -1;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:20:30 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/25 16:57:35 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list(t_p *list)
{
	if (list->args)
		list->args = NULL;
	if (list->cmd)
		list->cmd = NULL;
}

void	free2d(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

void	free_list(t_p *list)
{
	clear_list(list);
	free(list->process_pid);
	free2d(list->path);
	list->path = NULL;
	list->msh = NULL;
	list->env = NULL;
	close(list->pipe[0]);
	close(list->pipe[1]);
	list->pipe[0] = -1;
	list->pipe[1] = -1;
	safe_close(list, 0);
	safe_close(list, 1);
}

void	prepare_cmd(t_ast *ast, t_p *list, int *status)
{
	if (!ast || *status == -1)
		return ;
	if (ast->type == REDIRECT || ast->type == APPEND || ast->type == INDIRECT)
	{
		if (ast->type == REDIRECT)
			open_out_file(ast->right->args[0], list, 0, status);
		else if (ast->type == APPEND)
			open_out_file(ast->right->args[0], list, 1, status);
		else if (ast->type == INDIRECT)
			open_in_file(ast->right->args[0], list, status);
	}
	if (ast->type == CMD)
	{
		if (list->cmd == NULL)
			list->cmd = ast->args[0];
		if (list->args == NULL)
			list->args = ast->args;
	}
	prepare_cmd(ast->left, list, status);
	prepare_cmd(ast->right, list, status);
}

void	safe_close(t_p *list, int flag)
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

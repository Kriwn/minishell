/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:55 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/09 17:14:11 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void prepare_cmd(t_ast *ast,t_p *list)
{
	if (!ast)
		return ;
	if (ast->type == REDIRECT)
		list->fd_out = open(ast->right->args[0], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (ast->type == APPEND)
		list->fd_out = open(ast->right->args[0], O_RDWR | O_APPEND | O_CREAT, 0644);
	if (ast->type == INDIRECT)
		list->fd_in = open(ast->right->args[0], O_RDONLY);
	if (ast->type == CMD)
	{
		if (list->cmd == NULL)
			list->cmd = ast->args[0];
		if (ast->args[1] != NULL)
			list->args= ast->args;
	}
	prepare_cmd(ast->left,list);
	prepare_cmd(ast->right,list);
}

int	find_slash(char *command)
{
	size_t	i;

	if (!command)
		return (0);
	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	open_in_file(char *argv, t_p *list)
{
	list->fd_in = open(argv, O_RDONLY);
	if (list->fd_in == -1)
		printf("Cannot open in file %s\n", argv);
}

void	open_out_file(char *argv, t_p *list,int flag)
{
	int mode;

	if (flag == 1)
		mode= O_RDWR | O_TRUNC | O_CREAT;
	else
		mode = O_WRONLY | O_CREAT | O_APPEND;
	list->fd_out = open(argv, mode , 0644);
	if (list->fd_out == -1)
		printf("Cannot open out file %s\n", argv);
	dup2(list->fd_out, STDOUT_FILENO);
	close(list->fd_out);
}

void	pipe_write(t_p *list)
{
	close(list->pipe[0]);
	dup2(list->pipe[1], 1);
	close(list->pipe[1]);
}

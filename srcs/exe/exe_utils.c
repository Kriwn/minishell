/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:55 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/13 13:23:13 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int find_slash(char *command)
{
	size_t i;

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

void open_in_file(char *argv, t_p *list)
{
	list->fd_in = open(argv, O_RDONLY);
	if (list->fd_in == -1)
		printf("Cannot open in file %s\n", argv);
}

void open_out_file(char *argv, t_p *list, int flag)
{
	int mode;

	if (flag == 1)
		mode = O_RDWR | O_TRUNC | O_CREAT;
	else
		mode = O_WRONLY | O_CREAT | O_APPEND;
	list->fd_out = open(argv, mode, 0644);
	if (list->fd_out == -1)
		printf("Cannot open out file %s\n", argv);
	dup2(list->fd_out, STDOUT_FILENO);
	safe_close(list, 1);
}

void pipe_write(t_p *list)
{
	close(list->pipe[0]);
	dup2(list->pipe[1], 1);
	close(list->pipe[1]);
}

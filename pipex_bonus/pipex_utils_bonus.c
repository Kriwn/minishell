/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:31:09 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/19 13:06:39 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init(t_p *list, int argc)
{
	int	i;

	i = 0;
	list->pipe[0] = -1;
	list->pipe[1] = -1;
	list->argc = argc;
	list->process_pid = malloc(sizeof(int) * argc - 3);
	if (list->process_pid == NULL)
		ft_puterror("Malloc error", errno, list);
	list->here_doc = 0;
	list->infile = -1;
	list->count = 0;
	while (i < (argc - 3))
	{
		list->process_pid[i] = 0;
		i++;
	}
}

void	open_in_file(char *argv, t_p *list)
{
	list->infile = open(argv, O_RDONLY);
	if (list->infile == -1)
		ft_puterror(argv, errno, list);
}

void	open_out_file(char *argv, t_p *list, int flag)
{
	int	fd;

	if (flag)
		fd = open(argv, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(argv, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		ft_puterror(argv, errno, list);
	dup2(fd, STDOUT_FILENO);
	close(list->pipe[0]);
	close(list->pipe[1]);
	close(fd);
}

void	pipe_write(t_p *list)
{
	close(list->pipe[0]);
	dup2(list->pipe[1], 1);
	close(list->pipe[1]);
}

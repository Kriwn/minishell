/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:55 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/28 14:17:02 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// if (list->fd_in == -1)
	// 	piintf("Cannot open file %s\n", argv);
}

void	open_out_file(char *argv, t_p *list)
{
	int	fd;

	fd = open(argv, O_RDWR | O_TRUNC | O_CREAT, 0644);
	// if (fd == -1)
	// 	ft_puterror(argv, errno, list);
	dup2(fd, STDOUT_FILENO);
	close(list->pipe[0]);
	close(list->pipe[1]);
}

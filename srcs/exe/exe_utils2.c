/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:37:20 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/17 17:17:01 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_in_file(char *argv, t_p *list, int *status)
{
	if (list->fd_in != -1)
		safe_fd(list, 0);
	list->fd_in = open(argv, O_RDONLY);
	if (list->fd_in == -1)
	{
		ft_puterrstr("minishell: ");
		ft_puterrstr(argv);
		ft_puterrstr(": ");
		perror("");
	}
	*status = list->fd_in;
}

void	open_out_file(char *argv, t_p *list, int flag, int *status)
{
	int	mode;

	if (flag == 1)
		mode = O_RDWR | O_TRUNC | O_CREAT;
	else
		mode = O_WRONLY | O_CREAT | O_APPEND;
	if (list->fd_out != -1)
		safe_fd(list, 1);
	list->fd_out = open(argv, mode, 0644);
	if (list->fd_out == -1)
	{
		ft_puterrstr("minishell: ");
		ft_puterrstr(argv);
		ft_puterrstr(": ");
		perror("");
	}
	*status = list->fd_out;
}

void	pipe_write(t_p *list)
{
	safe_close(&list->pipe[0]);
	dup2(list->pipe[1], 1);
	safe_close(&list->pipe[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:37:20 by krwongwa          #+#    #+#             */
/*   Updated: 2025/02/05 22:08:50 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_in_file(char *argv, t_p *list, int *status)
{
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

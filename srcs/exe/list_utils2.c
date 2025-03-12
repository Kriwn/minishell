/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:35:20 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/12 19:39:21 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_close(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}

void	safe_fd(t_p *list, int flag)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:11:22 by jikarunw          #+#    #+#             */
/*   Updated: 2025/04/02 03:19:11 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_fd_out(int saved_stdout, t_p *list)
{
	if (list->fd_out != 1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	msh_echo(t_p *list)
{
	int	i;
	int	n_flag;
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	n_flag = 0;
	i = 1;
	handle_fd(list);
	if (!list->args[i]) // fix: NULL echo
	{
		handle_fd_out(saved_stdout, list);
		return (0);
	}
	if (!ft_strncmp(list->args[i], "-n", 3))
	{
		n_flag = 1;
		i++;
	}
	while (list->args[i])
	{
		ft_putstr_fd(list->args[i], STDOUT_FILENO);
		if (list->args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	handle_fd_out(saved_stdout, list);
	return (0);
}

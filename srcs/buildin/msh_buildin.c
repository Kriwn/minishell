/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_buildin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:47:52 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/05 01:31:20 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_fd(t_p *list)
{
	if (list->fd_out != 1)
	{
		dup2(list->fd_out, 1);
		close(list->pipe[0]);
		close(list->pipe[1]);
		safe_close(list, 1);
	}
}

//test cd
int	msh_execute_builtin(t_p *list)
{
	if (ft_strcmp(list->cmd, "echo") == 0)
		return (msh_echo(list));
	else if (ft_strcmp(list->cmd, "cd") == 0)
		return (msh_cd(list));
	else if (ft_strcmp(list->cmd, "pwd") == 0)
		return (msh_pwd(list));
	else if (ft_strcmp(list->cmd, "env") == 0)
		return (msh_env(list));
	else if (ft_strcmp(list->cmd, "export") == 0)
		return (msh_export(list));
	else if (ft_strcmp(list->cmd, "unset") == 0)
		return (msh_unset(list));
	else if (ft_strcmp(list->cmd, "exit") == 0)
		return (msh_exit(list->msh));
	return (EXIT_FAILURE);
}

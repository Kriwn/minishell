/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_buildin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:47:52 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/10 20:14:25 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_fd(t_p *list)
{
	if (list->fd_out != 1)
	{
		dup2(list->fd_out, 1);
		safe_close(&list->pipe[0]);
		safe_close(&list->pipe[1]);
		safe_fd(list, 1);
	}
}

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
		return (msh_exit(list));
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:11:22 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/05 02:52:21 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void expand_arguments(t_msh *shell, t_p *list)
{
	int i = 0;
	char *expanded;

	while (list->args[i])
	{
		if (ft_strcmp(list->args[i], "$?") == 0)
			expanded = ft_itoa(shell->code);
		else
			expanded = expand_variables(shell, list->args[i]);
		free(list->args[i]);  
		list->args[i] = expanded;  
		i++;
	}
}


int	msh_echo(t_p *list)
{
	int	i;
	int n_flag;
	int saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	n_flag = 0;
	i = 1;
	handle_fd(list);
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
	if (list->fd_out != 1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	return (0);
}

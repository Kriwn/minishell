/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:11:22 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/28 12:39:05 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_echo(t_msh **msh)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (!(*msh)->ast->args[i])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	if (!ft_strncmp((*msh)->ast->args[i], "-n", 3))
	{
		n_flag = 1;
		i++;
	}
	while ((*msh)->ast->args[i])
	{
		ft_putstr_fd((*msh)->ast->args[i], STDOUT_FILENO);
		if ((*msh)->ast->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

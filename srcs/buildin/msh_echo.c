/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:11:22 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/19 14:30:44 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	only_n(char *str, int *flag)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	*flag = 0;
	return (1);
}

void	put_arg(t_token *current)
{
	if (!current || !current->cmd)
		return ;
	ft_putstr_fd(current->cmd, STDOUT_FILENO);
	if (current->next)
		ft_putchar_fd(' ', STDOUT_FILENO);
}

int	msh_echo(t_msh *msh, t_token *token)
{
	int		nl_flag;
	t_token	*current;

	if (!msh || !token)
		return (EXIT_FAILURE);
	nl_flag = 1;
	current = token->next;
	if (!current)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	while (current && current->cmd && ft_strncmp(current->cmd, "-n", 2) == 0)
	{
		if (only_n(current->cmd + 2, &nl_flag))
			current = current->next;
		else
			break ;
	}
	while (current)
	{
		put_arg(current);
		current = current->next;
	}
	if (nl_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	msh->code = 12;
	return (EXIT_SUCCESS);
}

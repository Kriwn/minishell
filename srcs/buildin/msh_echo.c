/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:11:22 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/16 21:21:00 by jikarunw         ###   ########.fr       */
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
	ft_putstr_fd(current->str, STDOUT_FILENO);
	if (current->next)
		ft_putchar_fd(' ', STDOUT_FILENO);
}

int	msh_echo(t_msh *msh, t_token *token)
{
	int nl_flag = 1;
	t_token *current = token->next;

	if (!current)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	while (current && ft_strncmp(current->str, "-n", 2) == 0)
	{
		if (only_n(current->str + 2, &nl_flag))
			current = current->next;
		else
			break;
	}
	while (current)
	{
		put_arg(current);
		current = current->next;
	}
	if (nl_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	msh->code = 0;
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:35:32 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/23 22:04:14 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_is_digit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	msh_exit(t_msh *msh)
{
	int		i;
	char	*str;

	i = 0;
	if (msh->token->next)
	{
		str = msh->token->next->cmd;
		if (msh_is_digit_str(str))
			i = ft_atoi(str);
		else
		{
			ft_puterrorcmd("exit", 255);
			return (1);
		}
	}
	ft_putstr_fd("exit\n", 1);
	ft_free(msh);
	exit(i);
	return (0);
}

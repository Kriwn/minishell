/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:35:32 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/13 11:22:54 by krwongwa         ###   ########.fr       */
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

int	msh_exit(t_p *list)
{
	int		exit_status;
	char	*str;

	exit_status = 0;
	if (list->args[1])
	{
		if (msh_is_digit_str(list->args[1]) == 1)
			exit_status = ft_atoi(list->args[1]);
		else
		{
			ft_puterrstr("minishell: exit: numeric argument required\n");
			exit(2);
		}
		if (list->args[2] != NULL)
		{
			ft_puterrstr("minishell: exit: too many arguments\n");
			return (1);
		}
	}
	ft_putstr_fd("exit\n", 1);
	ft_free(list->msh);
	exit(exit_status);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:35:32 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/13 14:43:31 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free2d(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

int	msh_is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
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
	t_msh	*msh;

	exit_status = 0;
	msh = NULL;
	if (list->args[1])
	{
		if (msh_is_valid_number(list->args[1]))
			exit_status = ft_atoi(list->args[1]) % 256;
		else
		{
			ft_puterrstr("minishell: exit: numeric argument required\n");
			// free_list(msh->list);
			cleanup_and_exit(list->msh, 2);
		}
		if (list->args[2] != NULL)
		{
			ft_puterrstr("minishell: exit: too many arguments\n");
			return (1);
		}
	}
	ft_putstr_fd("exit\n", 1);
	free_list(list);
	cleanup_and_exit(list->msh, exit_status);
	return (0);
}

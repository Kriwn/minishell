/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_buildin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:47:52 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/16 20:54:27 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	(*init_builtin(char *str))(t_msh *msh)
{
	int	i;
	static void	*builtins[7][2] = {
		{"echo", msh_echo},
		{"cd", msh_cd},
		{"pwd", msh_pwd},
		{"export", NULL},
		{"unset", NULL},
		{"env", get_env},
		{"exit", NULL}};

	if (!str)
		return (NULL);
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(builtins[i][0], str))
			return (builtins[i][1]);
		i++;
	}

	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_buildin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:47:52 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/28 02:27:31 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int (*init_builtin(char *str))(t_msh *msh)
{
	int i;

	static struct {
		char *name;
		int (*func)(t_msh *);
	} builtins[] = {
		{"echo", msh_echo},
		{"cd", msh_cd},
		{"pwd", msh_pwd},
		{"export", NULL},
		{"unset", NULL},
		{"env", get_env},
		{"exit", msh_exit},
		{NULL, NULL}
	};

	if (!str)
		return (NULL);
	i = 0;
	while (builtins[i].name)
	{
		if (!ft_strcmp(builtins[i].name, str))
			return (builtins[i].func);
		i++;
	}
	return (NULL);
}

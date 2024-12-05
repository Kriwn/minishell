/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:26:50 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/05 15:36:29 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_export(t_msh *msh, char *arg)
{
	char	*key;
	char	*value;
	char	*temp;

	key = ft_strndup(arg, ft_strchr(arg, '=') - arg);
	value = ft_strdup(ft_strchr(arg, '=') + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (EXIT_FAILURE);
	}
	if (get_env_variable(msh->tuple, key))
		update_env_variable(msh->tuple, key, value);
	else
	{
		temp = ft_strjoin(key, "=");
		make_tuple(&msh->tuple, temp, value);
		free(temp);
	}
	free(key);
	free(value);
	return (EXIT_SUCCESS);
}

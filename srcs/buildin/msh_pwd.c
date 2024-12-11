/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:08:30 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/05 13:26:02 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*msh_help_pwd(t_tuple *list)
{
	char	*ans;

	ans = getcwd(NULL, 0);
	if (ans == NULL)
		ans = get_value_from_key(list, "PWD=");
	return (ans);
}

int	msh_pwd(t_msh *msh)
{
	char	*current_path;

	current_path = msh_help_pwd(msh->tuple);
	if (!current_path)
	{
		ft_putstr_fd("Error: Could not get current working directory\n",
						STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(current_path, STDOUT_FILENO);
	free(current_path);
	return (EXIT_SUCCESS);
}

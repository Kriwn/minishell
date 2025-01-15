/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:07:15 by jikarunw          #+#    #+#             */
/*   Updated: 2025/01/15 22:51:41 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char   *get_path(t_p *list)
{
	char *path;

	if (list->args[1] == NULL)
		return (get_value_from_key(list->msh->tuple, "HOME"));
	else
		path= list->args[1];
	return (path);
}

int change_dir(char *old_pwd, char *new_path,t_p *list)
{
	if (chdir(new_path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(new_path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (-1);
	}
	// updata_value_from_key(list->msh->tuple, "PWD", new_path);
	updata_value_from_key(list->msh->tuple, "OLDPWD", old_pwd);
	return (0);
}

// cd and cd ~ . .. fix PWD and OLDPWD to correct one
int	msh_cd(t_p *list)
{
	char *old_pwd;
	char *new_path;

	if (list->args[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	old_pwd = get_value_from_key(list->msh->tuple, "PWD");
	if (old_pwd == NULL)
		old_pwd = ft_getcwd();
	new_path = get_path(list);
	change_dir(old_pwd, new_path,list);
	// if (change_dir(old_pwd, new_path,list) == -1)
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

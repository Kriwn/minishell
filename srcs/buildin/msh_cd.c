/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:07:15 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/10 20:03:53 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_mem(char *pwd, char *new_path)
{
	if (pwd)
		free(pwd);
	if (new_path)
		free(new_path);
}

char	*get_path(t_p *list, char *pwd)
{
	char	*path;

	if (list->args[1] == NULL)
		return (copy(get_value_from_key(list->msh->tuple, "HOME")));
	else if (ft_strncmp(list->args[1], "-", 2) == 0 \
			&& ft_strlen(list->args[1]) == 1)
		return (copy(get_value_from_key(list->msh->tuple, "OLDPWD")));
	else
		return (list->args[1]);
}

int	change_dir(char *old_pwd, char *new_path, t_p *list)
{
	char	*temp;

	if (chdir(new_path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(new_path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (-1);
	}
	temp = ft_getcwd();
	if (temp == NULL)
		return (-2);
	updata_value_from_key(list->msh->tuple, "PWD", copy(temp));
	updata_value_from_key(list->msh->tuple, "OLDPWD", copy(old_pwd));
	free(temp);
	return (0);
}

int	msh_cd(t_p *list)
{
	char	*pwd;
	char	*new_path;

	if (list->args[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	pwd = copy(get_value_from_key(list->msh->tuple, "PWD"));
	if (!pwd)
		pwd = ft_getcwd();
	new_path = get_path(list, pwd);
	if (change_dir(pwd, new_path, list) == -1)
	{
		clear_mem(pwd, new_path);
		return (EXIT_FAILURE);
	}
	clear_mem(pwd, new_path);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:07:15 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/17 15:46:08 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env_variable(t_tuple *env, const char *key, const char *value)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

char	*get_env_variable(t_tuple *env, const char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	msh_cd(t_msh *msh, t_token *token)
{
	char	*target;
	char	*old_pwd;
	char	*new_pwd;

	if (!msh || !token)
		return (ft_putstr_fd("minishell: cd: internal error\n", STDERR_FILENO),
				EXIT_FAILURE);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("minishell: cd: getcwd");
		return (EXIT_FAILURE);
	}
	if (!token->next || !token->next->str)
	{
		target = get_env_variable(msh->tuple, "HOME=");
		if (!target)
		{
			free(old_pwd);
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	else if (!ft_strcmp(token->next->str, "-"))
	{
		target = get_env_variable(msh->tuple, "OLDPWD=");
		if (!target)
		{
			free(old_pwd);
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		ft_putendl_fd(target, STDOUT_FILENO);
	}
	else
	{
		target = token->next->str;
	}
	if (chdir(target) == -1)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (EXIT_FAILURE);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("minishell: cd: getcwd");
		free(old_pwd);
		return (EXIT_FAILURE);
	}
	update_env_variable(msh->tuple, "OLDPWD=", old_pwd);
	update_env_variable(msh->tuple, "PWD=", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (EXIT_SUCCESS);
}

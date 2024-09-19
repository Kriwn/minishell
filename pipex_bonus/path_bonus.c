/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:54:54 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/19 13:07:29 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	find_slash(char *command)
{
	size_t	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	check(char *env, char *path)
{
	if (*env != *path)
		return (0);
	else
	{
		while (*path)
		{
			if (*path != *env)
				return (0);
			path++;
			env++;
		}
		return (1);
	}
}

char	**find_path(char **env)
{
	size_t	i;
	char	**ans;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (env)
	{
		if (check(*env, "PATH="))
			break ;
		env++;
	}
	ans = ft_split((*env) + 5, ':');
	return (ans);
}

char	*cmd_path(char *command, char **path)
{
	char	*temp;
	char	*buff;
	size_t	i;

	if (!command)
		return (NULL);
	if (path == NULL)
		if (access(command, X_OK) == 0)
			return (command);
	i = 0;
	while (path != NULL && path[i])
	{
		temp = ft_strjoin(path[i], "/");
		buff = temp;
		temp = ft_strjoin(temp, command);
		free(buff);
		if (access(temp, X_OK) == 0)
			return (temp);
		free(temp);
		i++;
	}
	return (command);
}

void	run_cmd(char *command, char **env, int infile, t_p *list)
{
	char	**args;
	char	**path;
	char	*cmd;
	int		num;

	path = NULL;
	args = ft_split(command, ' ');
	if (!find_slash(command))
		path = find_path(env);
	cmd = cmd_path(args[0], path);
	dup2(infile, 0);
	close(infile);
	if (execve(cmd, args, env) == -1)
	{
		num = ft_puterrorcmd(args[0], errno);
		if (args)
			args = free2darr(args);
		if (path)
			path = free2darr(path);
		freelist(list);
		exit(num);
	}
}

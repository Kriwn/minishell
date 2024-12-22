/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:55 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/21 21:37:34 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*myft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	n;
	char	*str;

	i = 0;
	n = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[n])
	{
		str[n + i] = s2[n];
		n++;
	}
	str[n + i] = '\0';
	return (str);
}

char *find_path(char *cmd, char **path)
{
	int i;
	char *temp;
	char *cmd_path;
	char **temp_path;

	i = 0;
	temp_path = path;
	if (find_slash(cmd))
			return (cmd);
	while (temp_path[i])
	{
		temp = myft_strjoin(temp_path[i], "/");
		cmd_path = myft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return NULL;
}

int find_slash(char *command)
{
	size_t i;

	if (!command)
		return (0);
	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

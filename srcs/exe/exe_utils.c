/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:55 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/18 22:11:02 by krwongwa         ###   ########.fr       */
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

void open_in_file(char *argv, t_p *list,int *status)
{
	list->fd_in = open(argv, O_RDONLY | O_CLOEXEC);
	if (list->fd_in == -1)
	{
		ft_puterrstr("minishell: ");
		ft_puterrstr(argv);
		ft_puterrstr(": ");
		perror("");
	}
	*status = list->fd_in;
}

void open_out_file(char *argv, t_p *list, int flag, int *status)
{
	int mode;

	if (flag == 1)
		mode = O_RDWR | O_TRUNC | O_CREAT;
	else
		mode = O_WRONLY | O_CREAT | O_APPEND;
	list->fd_out = open(argv, mode, 0644);
	if (list->fd_out == -1)
	{
		ft_puterrstr("minishell: ");
		ft_puterrstr(argv);
		ft_puterrstr(": ");
		perror("");

	}
	*status = list->fd_out;
}

void pipe_write(t_p *list)
{
	close(list->pipe[0]);
	dup2(list->pipe[1], 1);
	close(list->pipe[1]);
}

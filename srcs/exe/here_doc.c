/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:01 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/18 18:23:07 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_here_doc(t_p *list, char *getline, int fd[2])
{
	if (getline)
		free(getline);
	getline = NULL;
	list->fd_in = dup(fd[0]);
	close(fd[0]);
	close(fd[1]);
}

int	check_new_line(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int	check_here_doc(char *str, char *ans)
{
	char	*ans_newline;
	int		n;
	size_t	i;

	i = 0;
	ans_newline = ft_strjoin(ans, "\n");
	n = 0;
	while (str[i] != '\0' && ans_newline[i] != '\0')
	{
		if (str[i] != ans_newline[i])
		{
			free(ans_newline);
			return (0);
		}
		i++;
	}
	n = 1;
	if (str[i] != '\0' || ans_newline[i] != '\0')
		n = 0;
	free(ans_newline);
	return (n);
}

int	gethere_doc(char **getline, char *str)
{
	char	buff[2];
	char	*temp;

	temp = NULL;
	buff[1] = '\0';
	while (!check_new_line(*getline))
	{
		if (read(0, &buff, 1) == 0)
			return (-1);
		temp = *getline;
		*getline = ft_strjoin(*getline, buff);
		free(temp);
	}
	return (0);
}

int	do_here_doc(char *str, t_p *list)
{
	char	*getline;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_puterror("Pipe error", errno, list);
	while (1)
	{
		write(1, "> ", 2);
		getline = ft_calloc(1, 1);
		if (gethere_doc(&getline, str) == -1)
			break ;
		if (check_here_doc(getline, str))
			break ;
		write(fd[1], getline, ft_strlen(getline));
		if (getline)
			free(getline);
	}
	clear_here_doc(list, getline, fd);
	return (1);
}

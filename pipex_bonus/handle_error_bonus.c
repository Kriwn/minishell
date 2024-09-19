/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:58:41 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/19 20:05:04 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_puterror(char *s, int errnum, t_p *list)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(s, 2);
	write(2, ": ", 2);
	if (errnum == 2)
		ft_putstr_fd("No such file or directory", 2);
	else
		ft_putstr_fd(strerror(errnum), 2);
	write(2, "\n", 1);
	if (list)
		freelist(list);
	exit(errnum);
}

int	ft_puterrorcmd(char *s, int errnum)
{
	if (errnum == 2)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(s, 2);
		write(2, ": ", 2);
		if (find_slash(s))
			ft_putstr_fd("No such file or directory\n", 2);
		else
			ft_putstr_fd("command not found\n", 2);
		return (127);
	}
	else if (errnum == 13)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(s, 2);
		write(2, ": ", 2);
		ft_putstr_fd("permision denine \n", 2);
		return (126);
	}
	return (0);
}

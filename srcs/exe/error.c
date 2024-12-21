/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:39:56 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/21 21:48:43 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterrstr(char *s)
{
	if (!s)
		return ;
	write(2, s, ft_strlen(s));
}

// void	ft_puterror(char *s, int errnum, t_p *list)
// {
// 	ft_putstr_fd("pipex: ", 2);
// 	ft_putstr_fd(s, 2);
// 	write(2, ": ", 2);
// 	if (errnum == 2)
// 		ft_putstr_fd("No such file or directory", 2);
// 	else
// 		ft_putstr_fd(strerror(errnum), 2);
// 	write(2, "\n", 1);
// 	if (list)
// 		freelist(list);
// 	exit(errnum);
// }

int	ft_puterrorcmd(char *s, int errnum)
{
	dprintf(2,"Errnum is %d\n",errnum);
	if (errnum == 14 || errnum == 2) // in orb maybe is 2
	{
		// ft_puterrstr("pipex: ");
		ft_puterrstr(s);
		write(2, ": ", 2);
		if (find_slash(s))
			ft_puterrstr("No such file or directory\n");
		else
			ft_puterrstr("command not found\n");
		return (127);
	}
	else if (errnum == 13)
	{
		// ft_puterrstr("pipex: ");
		ft_puterrstr(s);
		write(2, ": ", 2);
		ft_puterrstr("permision denine \n");
		return (126);
	}
	return (errnum);
}

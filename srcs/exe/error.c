/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:39:56 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/10 08:37:29 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterrstr(char *s)
{
	if (!s)
		return ;
	write(2, s, ft_strlen(s));
}

/*
 in orb maybe is 2
*/

int	ft_puterrorcmd(char *s, int errnum)
{
	// dprintf(2,"Errnum is %d\n",errnum);
	if (errnum == 14 || errnum == 2) // in orb maybe is 2
	{
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
		ft_puterrstr(s);
		write(2, ": ", 2);
		ft_puterrstr("permision denine \n");
		return (126);
	}
	return (errnum);
}

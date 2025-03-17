/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:39:56 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/13 17:06:36 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterrstr(char *s)
{
	if (!s)
		return ;
	write(2, s, ft_strlen(s));
}

int	ft_puterrorcmd(char *s, int errnum)
{
	if (errnum == 14 || errnum == 2)
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
		if (access(s,F_OK) == 0 && find_slash(s))
			ft_puterrstr("Is a directory\n");
		else if (access(s,R_OK) == 0)
		{
			ft_puterrstr("command not found\n");
			return (127);
		}
		else
			ft_puterrstr("Permission denied\n");
		return (126);
	}
	return (errnum);
}

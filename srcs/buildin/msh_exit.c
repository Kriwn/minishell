/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:35:32 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/27 18:43:48 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_exit(t_msh *msh)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_free(msh);
	exit(0);
	return (0);
}

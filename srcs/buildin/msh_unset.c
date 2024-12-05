/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:27:19 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/05 15:29:52 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_unset(t_msh *msh, char *arg)
{
	remove_tuple(&msh->tuple, arg);
	return (EXIT_SUCCESS);
}

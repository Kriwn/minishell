/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:42:26 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/27 22:57:05 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_unset(t_p *list)
{
	remove_tuple(&list->msh->tuple, list->args[1]);
	return (EXIT_SUCCESS);
}

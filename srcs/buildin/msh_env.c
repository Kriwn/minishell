/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:04:26 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/25 14:04:20 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int msh_env(t_p *list)
{
	t_msh *msh;

	msh = list->msh;
	print_tuple(msh->tuple);
	return (EXIT_SUCCESS);
}

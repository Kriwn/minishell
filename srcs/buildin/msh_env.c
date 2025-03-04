/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:04:26 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/28 00:57:43 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// env > a not working
int msh_env(t_p *list)
{
	t_msh *msh;

	if (list->fd_out != 1)
	{
		dup2(list->fd_out, 1);
		close(list->pipe[0]);
		close(list->pipe[1]);
		safe_close(list, 1);
	}
	msh = list->msh;
	print_tuple(msh->tuple);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:04:26 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/15 22:42:09 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// env > a not working
int msh_env(t_p *list)
{
	t_msh *msh;
	int saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	handle_fd(list);
	msh = list->msh;
	print_tuple(msh->tuple);
	if (list->fd_out != 1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	return (EXIT_SUCCESS);
}

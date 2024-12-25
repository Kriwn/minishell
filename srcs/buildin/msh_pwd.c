/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:08:30 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/25 16:00:01 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(t_p *list)
{
	char	*current_path;

	current_path = get_value_from_key(list->msh->tuple,"PWD");
	if (!current_path)
	{
		dprintf(2, "minishell: pwd: PWD not set\n");
	}
	ft_putendl_fd(current_path, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

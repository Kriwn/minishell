/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:08:30 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/28 00:00:53 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getcwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (NULL);
	return (path);
}

// need flag to do return or print 
int	msh_pwd(t_p *list)
{
	char	*current_path;

	current_path = get_value_from_key(list->msh->tuple,"PWD");
	if (!current_path)
	{
		current_path = ft_getcwd();
		free (current_path);
		return (EXIT_SUCCESS);
	}
	ft_putendl_fd(current_path, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

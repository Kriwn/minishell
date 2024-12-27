/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_buildin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:47:52 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/28 00:18:48 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	msh_handle_builtin(t_msh *msh)
// {
// 	if (ft_strcmp(msh->ast->args[0], "export") == 0)
// 	{
// 		if (!msh->ast->args[1])
// 		{
// 			ft_putstr_fd("minishell: export: not enough arguments\n",
// 					STDERR_FILENO);
// 			msh->code = 1;
// 			return (EXIT_FAILURE);
// 		}
// 		return (msh_export(msh, msh->ast->args[1]));
// 	}
// 	else if (ft_strcmp(msh->ast->args[0], "unset") == 0)
// 	{
// 		if (!msh->ast->args[1])
// 		{
// 			ft_putstr_fd("minishell: unset: not enough arguments\n",
// 					STDERR_FILENO);
// 			msh->code = 1;
// 			return (EXIT_FAILURE);
// 		}
// 		return (msh_unset(msh, msh->ast->args[1]));
// 	}
// }

int	msh_execute_builtin(t_p *list)
{
	if (ft_strcmp(list->cmd, "echo") == 0)
	{
		dprintf(2,"DO echo\n");
		for (int i = 0;list->args[i];i++)
		{
			dprintf(2,"Args: %s\n",list->args[i]);
		}
		return (msh_echo(list));
	}
	else if (ft_strcmp(list->cmd, "cd") == 0)
		dprintf(2,"DO CD\n");
		// return (msh_cd(msh, msh->ast->args[1]));
	else if (ft_strcmp(list->cmd, "pwd") == 0)
		return (msh_pwd(list));
	else if (ft_strcmp(list->cmd, "env") == 0)
	{
		dprintf(2,"DO env\n");
		return (msh_env(list));
	}
	else if (ft_strcmp(list->cmd, "export") == 0)
	{
		dprintf(2,"DO export\n");
		return (msh_export(list));
	}
	else if (ft_strcmp(list->cmd, "unset") == 0)
	{
		dprintf(2,"DO unset\n");
		return (msh_unset(list));
	}
	else if (ft_strcmp(list->cmd, "exit") == 0)
		return (msh_exit(list->msh));
	// msh_handle_builtin(msh);
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buildin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:53:16 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/14 15:22:34 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_build_in_command(char *word, int *isBuildIn)
{
	if (ft_strcmp(word, "echo") == 0)
		*isBuildIn = 0;
	else if (ft_strcmp(word, "cd") == 0)
		*isBuildIn = 0;
	else if (ft_strcmp(word, "pwd") == 0)
		*isBuildIn = 0;
	else if (ft_strcmp(word, "export") == 0)
		*isBuildIn = 0;
	else if (ft_strcmp(word, "unset") == 0)
		*isBuildIn = 0;
	else if (ft_strcmp(word, "env") == 0)
		*isBuildIn = 0;
	else if (ft_strcmp(word, "exit") == 0)
		*isBuildIn = 0;
	else
		*isBuildIn = 1;
}

void	is_build_in_command(t_ast *ast, int *isBuildIn)
{
	char	*word;

	if (!ast || *isBuildIn == 0 || *isBuildIn == 1)
		return ;
	if (ast->type == CMD)
	{
		if (ast->left == NULL)
			word = ast->args[0];
		else
			word = ast->left->args[0];
		check_build_in_command(word, isBuildIn);
		return ;
	}
	else
	{
		is_build_in_command(ast->left, isBuildIn);
		is_build_in_command(ast->right, isBuildIn);
	}
}

void	exe_single_cmd(t_ast *ast, t_p *list)
{
	int	status;

	status = 1;
	prepare_cmd(ast, list, &status);
	if (status == -1)
	{
		*list->code = 1;
		return ;
	}
	*list->code = msh_execute_builtin(list);
}

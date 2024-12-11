/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:49:36 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/11 21:45:34 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_build_in_command(char *word)
{
	if (ft_strcmp(word, "echo") == 0)
		return (0);
	else if (ft_strcmp(word, "pwd") == 0)
		return (0);
	else if (ft_strcmp(word, "cd") == 0)
		return (0);
	else if (ft_strcmp(word, "env") == 0)
		return (0);
	return (1);
}

int	is_build_in_command(t_ast *ast)
{
	char *word;

	printf("In build in\n");
	if (ast->left->type == CMD)
		word = ast->left->args[0];
	else
		word = ast->left->left->args[0];
	printf("word is %s\n",word);
	return check_build_in_command(word);
}

int exe_single_cmd(t_msh *msh, t_ast *ast, t_p *list)
{
	if (!is_build_in_command(ast))
		return (run_build_in(ast));
	else
		return (run_command(ast, list));
}

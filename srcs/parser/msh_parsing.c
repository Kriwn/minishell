/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/25 05:10:59 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*msh_get_tokens(t_token **tokens)
{
	t_msh	*msh;

	if (!tokens || !*tokens)
		return (NULL);
	return (msh_get_pipe(tokens));
}

// t_ast	*msh_get_tokens(t_token **tokens)
// {
// 	t_token	*current;
// 	t_ast	*root;
// 	t_ast	*current_node;
// 	current = *tokens;
// 	if (!current)
// 		return (NULL);
// 	root = msh_init_ast(CMD_GROUP);
// 	current_node = root;
// 	while (current)
// 	{
// 		if (current->type == CMD)
// 		{
// 			current_node->left = msh_init_ast(CMD);
// 			current_node->left->args = malloc(sizeof(char *) * 2);
// 			if (!current_node->left->args)
// 				return (NULL);
// 			current_node->left->args[0] = ft_strdup(current->cmd);
// 			current_node->left->args[1] = NULL;
// 			current_node = current_node->left;
// 		}
// 		else if (current->type == ENV_VAR)
// 		{
// 			current_node->right = msh_init_ast(ENV_VAR);
// 			current_node->right->args = malloc(sizeof(char *) * 2);
// 			if (!current_node->right->args)
// 				return (NULL);
// 			current_node->right->args[0] = ft_strdup(current->cmd);
// 			current_node->right->args[1] = NULL;
// 			current_node = current_node->right;
// 		}
// 		current = current->next;
// 	}
// 	return (root);
// }

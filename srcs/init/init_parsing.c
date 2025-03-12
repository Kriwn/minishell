/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:59:11 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/12 19:46:20 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*msh_init_ast(t_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*create_ast_node(t_token *token)
{
	t_ast	*node;

	if (!token || !token->cmd)
		return (NULL);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

char	**allocate_ast_args(char *cmd)
{
	char	**args;

	args = malloc(sizeof(char *) * 2);
	if (!args)
		return (NULL);
	args[0] = ft_strdup(cmd);
	if (!args[0])
	{
		free(args);
		return (NULL);
	}
	args[1] = NULL;
	return (args);
}

t_ast	*file_ast_node(t_token *token)
{
	t_ast	*node;

	node = create_ast_node(token);
	if (!node)
		return (NULL);
	node->args = allocate_ast_args(token->cmd);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	free(token->cmd);
	free(token);
	return (node);
}

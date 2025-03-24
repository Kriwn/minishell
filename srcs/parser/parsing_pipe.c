/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:03:44 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/24 17:32:57 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*create_env_var_node(t_token *current)
{
	t_ast	*env_var_node;

	env_var_node = msh_init_ast(ENV_VAR);
	env_var_node->args = malloc(sizeof(char *) * 2);
	if (!env_var_node->args)
		return (NULL);
	env_var_node->args[0] = ft_strdup(current->cmd);
	env_var_node->args[1] = NULL;
	return (env_var_node);
}

t_ast	*create_pipe_node(t_token **tokens, t_token *tmp, t_token *next_token)
{
	t_ast	*pipe_node;
	t_ast	*command_group;

	pipe_node = msh_init_ast(next_token->type);
	(*tokens)->next = NULL;
	command_group = msh_init_ast(CMD_GROUP);
	command_group->left = msh_get_redirect(&tmp);
	pipe_node->left = command_group;
	pipe_node->right = msh_get_pipe(&(next_token->next));
	free(next_token->cmd);
	free(next_token);
	return (pipe_node);
}

t_ast	*msh_get_pipe(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next_token;
	t_ast	*command_group;

	if (!tokens || !*tokens)
		return (NULL);
	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if (next_token->type == PIPE && (!next_token->next || \
			next_token->next->type == PIPE))
			return (NULL);
		if (next_token->type == PIPE)
			return (create_pipe_node(tokens, tmp, next_token));
		*tokens = next_token;
	}
	command_group = msh_init_ast(CMD_GROUP);
	command_group->left = msh_get_redirect(&tmp);
	return (command_group);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/20 23:26:36 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*file_ast_node(t_token *token)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = token->cmd;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	free(token);
	return (node);
}

t_ast	*msh_get_cmd(t_token **tokens)
{
	t_ast	*command_node;
	int		arg_count;

	command_node = msh_init_ast(CMD);
	arg_count = count_cmd_arg(*tokens);
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->args)
		return (NULL);
	add_cmd_arg(command_node, tokens, arg_count);
	return (command_node);
}

t_ast	*msh_get_redirect(t_token **tokens)
{
	t_token	*tmp;
	t_ast	*redirect_node;
	t_token	*next_token;

	if (!*tokens)
		return (NULL);
	tmp = *tokens;
	if ((*tokens)->type >= REDIRECT && (*tokens)->type <= HEREDOC)
		return (create_file_list_redir(tokens, tmp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type >= REDIRECT
			&& (*tokens)->next->type <= HEREDOC)
		{
			redirect_node = msh_init_ast((*tokens)->next->type);
			(*tokens)->next = next_token->next->next;
			redirect_node->left = msh_get_redirect(&tmp);
			redirect_node->right = file_ast_node((next_token->next));
			return (free(next_token->cmd), free(next_token), redirect_node);
		}
		*tokens = next_token;
	}
	return (msh_get_cmd(&tmp));
}

t_ast	*msh_get_pipe(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next_token;
	t_ast	*pipe_node;

	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == PIPE)
		{
			pipe_node = msh_init_ast((*tokens)->next->type);
			(*tokens)->next = NULL;
			pipe_node->left = msh_get_redirect(&tmp);
			pipe_node->right = msh_get_pipe(&(next_token->next));
			free(next_token->cmd);
			free(next_token);
			return (pipe_node);
		}
		*tokens = next_token;
	}
	return (msh_get_redirect(&tmp));
}

t_ast	*msh_get_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	// display_tokens(*tokens);
	test_delete_heredoc(tokens);
	return (msh_get_pipe(tokens));
}

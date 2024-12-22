/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/21 21:47:18 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*msh_get_heredoc_word(t_token **token)
{
	
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
	if ((*tokens)->type >= INDIRECT && (*tokens)->type <= HEREDOC)
		return (create_file_list_redir(tokens, tmp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type >= INDIRECT
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
	t_ast	*command_group;

	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if (next_token->type == PIPE)
		{
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
		*tokens = next_token;
	}
	command_group = msh_init_ast(CMD_GROUP);
	command_group->left = msh_get_redirect(&tmp);
	return (command_group);
}

t_ast	*msh_get_tokens(t_token **tokens)
{
	t_msh	*msh;

	if (!tokens || !*tokens)
		return (NULL);
	return (msh_get_pipe(tokens));
}

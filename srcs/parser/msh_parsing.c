/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/24 01:12:38 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*msh_get_expand(t_token **token)
{
	t_ast	*expand_node;

	if (!token || !*token || (*token)->type != ENV_VAR)
		return (NULL);
	expand_node = msh_init_ast(ENV_VAR);
	if (!expand_node)
		return (NULL);
	expand_node->args = malloc(sizeof(char *) * 2);
	if (!expand_node->args)
	{
		free(expand_node);
		return (NULL);
	}
	expand_node->args[0] = ft_strdup((*token)->cmd);
	expand_node->args[1] = NULL;
	return (expand_node);
}

t_ast	*msh_get_heredoc_word(t_token **token)
{
	t_ast	*heredoc_node;
	t_ast	*heredoc_word_node;
	t_token	*next_token;

	if (!token || !*token || (*token)->type != HEREDOC)
		return (NULL);
	heredoc_node = msh_init_ast(HEREDOC);
	if (!heredoc_node)
		return (NULL);
	*token = (*token)->next;
	if (!msh_validate_heredoc_token(token, heredoc_node))
		return (NULL);
	heredoc_word_node = msh_init_heredoc_word_node(heredoc_node, *token);
	if (!heredoc_word_node)
		return (NULL);
	heredoc_node->right = heredoc_word_node;
	free((*token)->cmd);
	next_token = (*token)->next;
	free(*token);
	*token = next_token;
	return (heredoc_node);
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

	if (!*tokens)
		return (NULL);
	tmp = *tokens;
	if ((*tokens)->type >= INDIRECT && (*tokens)->type <= HEREDOC)
	{
		if ((*tokens)->type == HEREDOC)
			return (msh_get_heredoc_word(tokens));
		return (create_file_list_redir(tokens, tmp));
	}
	while (*tokens && (*tokens)->next)
	{
		if ((*tokens)->next->type >= INDIRECT
			&& (*tokens)->next->type <= HEREDOC)
		{
			if ((*tokens)->next->type == HEREDOC)
				return (msh_handle_heredoc(tokens));
			return (msh_handle_redirect(tokens, &tmp));
		}
		*tokens = (*tokens)->next;
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
	t_token	*current;
	t_ast	*ast_root;
	t_msh	*msh;

	if (!tokens || !*tokens)
		return (NULL);
	current = *tokens;
	while (current)
	{
		if (current->type == ENV_VAR || current->type == HEREDOC)
		{
			if (current->cmd)
				current->cmd = msh_expand_variable(msh, current->cmd);
		}
		current = current->next;
	}
	ast_root = msh_get_pipe(tokens);
	return (ast_root);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:09:32 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/24 21:15:31 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*msh_init_heredoc_word_node(t_ast *heredoc_node, t_token *token)
{
	t_ast	*heredoc_word_node;

	heredoc_word_node = msh_init_ast(HEREDOC_WORD);
	if (!heredoc_word_node)
	{
		free(heredoc_node);
		return (NULL);
	}
	heredoc_word_node->args = malloc(sizeof(char *) * 2);
	if (!heredoc_word_node->args)
	{
		free(heredoc_node);
		free(heredoc_word_node);
		return (NULL);
	}
	heredoc_word_node->args[0] = ft_strdup(token->cmd);
	heredoc_word_node->args[1] = NULL;
	return (heredoc_word_node);
}

int	msh_validate_heredoc_token(t_token **token, t_ast *heredoc_node)
{
	t_msh	*msh;

	if (!*token || (*token)->type != CMD)
	{
		free(heredoc_node);
		return (0);
	}
	if ((*token)->cmd && (*token)->cmd[0] == '\'')
	{
		heredoc_node->args = malloc(sizeof(char *) * 2);
		if (!heredoc_node->args)
		{
			free(heredoc_node);
			return (0);
		}
		heredoc_node->args[0] = ft_strdup((*token)->cmd);
		heredoc_node->args[1] = NULL;
		return (1);
	}
	heredoc_node->args = malloc(sizeof(char *) * 2);
	if (!heredoc_node->args)
	{
		free(heredoc_node);
		return (0);
	}
	// heredoc_node->args[0] = msh_expand_variable(msh, (*token)->cmd);
	heredoc_node->args[1] = NULL;
	return (1);
}

t_ast	*msh_handle_heredoc(t_token **tokens)
{
	t_ast	*redirect_node;
	t_token	*next_token;

	next_token = (*tokens)->next;
	redirect_node = msh_init_ast(HEREDOC);
	(*tokens)->next = next_token->next->next;
	redirect_node->left = msh_get_redirect(tokens);
	redirect_node->right = msh_get_heredoc_word(&next_token->next);
	return (redirect_node);
}

t_ast	*msh_handle_redirect(t_token **tokens, t_token **tmp)
{
	t_ast	*redirect_node;
	t_token	*next_token;

	next_token = (*tokens)->next;
	redirect_node = msh_init_ast(next_token->type);
	(*tokens)->next = next_token->next->next;
	redirect_node->left = msh_get_redirect(tmp);
	redirect_node->right = file_ast_node(next_token->next);
	free(next_token->cmd);
	free(next_token);
	return (redirect_node);
}

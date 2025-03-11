/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_03.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:08:17 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/11 16:35:09 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*handle_heredoc(t_token **tokens, t_token *tmp)
{
	t_ast	*redirect_node;
	t_token	*next_token;

	next_token = (*tokens)->next;
	redirect_node = msh_init_ast(HEREDOC);
	(*tokens)->next = next_token->next->next;
	redirect_node->left = msh_get_redirect(&tmp);
	redirect_node->right = msh_get_heredoc_word(&next_token->next);
	return (redirect_node);
}

t_ast	*create_heredoc_node(t_token **token)
{
	t_ast	*heredoc_node;

	heredoc_node = msh_init_ast(HEREDOC);
	if (!heredoc_node)
		return (NULL);
	*token = (*token)->next;
	if (!*token || (*token)->type != CMD)
	{
		free(heredoc_node);
		return (NULL);
	}
	return (heredoc_node);
}

t_ast	*create_heredoc_word_node(t_token **token)
{
	t_ast	*heredoc_word_node;

	heredoc_word_node = msh_init_ast(HEREDOC_WORD);
	if (!heredoc_word_node)
		return (NULL);
	heredoc_word_node->args = malloc(sizeof(char *) * 2);
	if (!heredoc_word_node->args)
	{
		free(heredoc_word_node);
		return (NULL);
	}
	heredoc_word_node->args[0] = ft_strdup((*token)->cmd);
	heredoc_word_node->args[1] = NULL;
	return (heredoc_word_node);
}

t_ast	*msh_get_heredoc_word(t_token **token)
{
	t_ast	*heredoc_node;
	t_ast	*heredoc_word_node;
	t_token	*next_token;

	if (!token || !*token || (*token)->type != HEREDOC)
		return (NULL);
	heredoc_node = create_heredoc_node(token);
	if (!heredoc_node)
		return (NULL);
	heredoc_word_node = create_heredoc_word_node(token);
	if (!heredoc_word_node)
	{
		free_ast(heredoc_node);
		return (NULL);
	}
	heredoc_node->right = heredoc_word_node;
	next_token = (*token)->next;
	free((*token)->cmd);
	free(*token);
	*token = next_token;
	if (*token && (*token)->type == HEREDOC)
		heredoc_node->left = msh_get_heredoc_word(token);
	return (heredoc_node);
}

t_ast	*handle_redirect(t_token **tokens, t_token *tmp)
{
	t_ast	*redirect_node;
	t_token	*next_token;

	next_token = (*tokens)->next;
	redirect_node = msh_init_ast((*tokens)->next->type);
	(*tokens)->next = next_token->next->next;
	redirect_node->left = msh_get_redirect(&tmp);
	redirect_node->right = file_ast_node((next_token->next));
	free(next_token->cmd);
	free(next_token);
	return (redirect_node);
}

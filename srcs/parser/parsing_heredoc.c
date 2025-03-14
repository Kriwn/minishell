/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:03:40 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/14 16:44:58 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		free_ast(heredoc_word_node);
		return (NULL);
	}
	heredoc_word_node->args[0] = ft_strdup((*token)->cmd);
	if (!heredoc_word_node->args[0])
	{
		free(heredoc_word_node->args);
		free_ast(heredoc_word_node);
		return (NULL);
	}
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
	// if (!(*token)->next || (*token)->next->type != CMD) // segmentation fault ?
	// {
	// 	free_ast(heredoc_node);
	// 	return (NULL);
	// }
	heredoc_word_node = create_heredoc_word_node(token);
	if (!heredoc_word_node)
	{
		free_cmd_args(heredoc_word_node);
		free_cmd_tokens(token);
		free_ast(heredoc_node);
		return (NULL);
	}
	heredoc_node->right = heredoc_word_node;
	next_token = (*token)->next;
	free_cmd_tokens(token);
	*token = next_token;
	if (*token && (*token)->type == HEREDOC)
		heredoc_node->left = msh_get_heredoc_word(token);
	return (heredoc_node);
}

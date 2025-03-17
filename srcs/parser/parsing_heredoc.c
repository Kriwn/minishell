/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:03:40 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/18 00:56:55 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*create_heredoc_node(t_token **token)
{
	t_ast	*heredoc_node;
	t_token	*next_token;

	if (!token || !*token || (*token)->type != HEREDOC)
		return (NULL);
	heredoc_node = msh_init_ast(HEREDOC);
	if (!heredoc_node)
		return (NULL);
	next_token = (*token)->next;
	free((*token)->cmd);
	free(*token);
	*token = next_token;
	if (!*token || (*token)->type != CMD)
	{
		free(heredoc_node);
		free_cmd_tokens(token);
		return (NULL);
	}
	return (heredoc_node);
}

t_ast	*allocate_heredoc_word(void)
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
	heredoc_word_node->args[0] = NULL;
	heredoc_word_node->args[1] = NULL;
	return (heredoc_word_node);
}

t_ast	*create_heredoc_word_node(t_token **token)
{
	t_ast	*heredoc_word_node;
	t_token	*next_token;

	if (!token || !*token)
		return (NULL);
	heredoc_word_node = allocate_heredoc_word();
	if (!heredoc_word_node)
		return (NULL);
	heredoc_word_node->args[0] = ft_strdup((*token)->cmd);
	if (!heredoc_word_node->args[0])
	{
		free(heredoc_word_node->args);
		free(heredoc_word_node);
		return (NULL);
	}
	next_token = (*token)->next;
	free((*token)->cmd);
	free(*token);
	*token = next_token;
	return (heredoc_word_node);
}

t_ast	*msh_get_heredoc_node(t_token **token)
{
	t_ast	*new_heredoc;

	new_heredoc = create_heredoc_node(token);
	if (!new_heredoc)
		return (NULL);
	new_heredoc->right = create_heredoc_word_node(token);
	if (!new_heredoc->right)
	{
		free_heredoc_nodes(new_heredoc);
		return (NULL);
	}
	return (new_heredoc);
}

t_ast	*msh_get_heredoc_word(t_token **token)
{
	t_ast	*heredoc_root;
	t_ast	*last_heredoc;
	t_ast	*new_heredoc;

	heredoc_root = NULL;
	last_heredoc = NULL;
	while (token && *token && (*token)->type == HEREDOC)
	{
		new_heredoc = msh_get_heredoc_node(token);
		if (!new_heredoc)
		{
			free_heredoc_nodes(heredoc_root);
			return (NULL);
		}
		if (!heredoc_root)
			heredoc_root = new_heredoc;
		else
			last_heredoc->left = new_heredoc;
		last_heredoc = new_heredoc;
	}
	return (heredoc_root);
}

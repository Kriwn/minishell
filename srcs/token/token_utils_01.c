/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 20:56:54 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/11 16:42:11 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->cmd = ft_strdup(value);
	if (!token->cmd)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!new_token)
		return ;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
		new_token->prev = last;
	}
}

void	add_word_token_if_valid(char **start, char **input, t_token **tokens)
{
	char	*word;
	t_token	*token;

	if (*input > *start)
	{
		word = ft_strndup(*start, *input - *start);
		if (!word)
		{
			ft_putstr_fd("Error: Malloc failed in \
				add_word_token_if_valid.\n", 2);
			return ;
		}
		token = new_token(CMD, word);
		if (!token)
		{
			free(word);
			return ;
		}
		add_token_to_list(tokens, token);
		free(word);
	}
}

void	parse_cmd(char **input, t_token **tokens)
{
	char	*start;
	int		in_quote;
	char	quote_char;

	start = *input;
	in_quote = 0;
	quote_char = '\0';
	while (**input)
	{
		update_quote_status(**input, &in_quote, &quote_char);
		if (!in_quote && ft_strchr(" \t\n><|", **input))
			break ;
		(*input)++;
	}
	add_word_token_if_valid(&start, input, tokens);
}

void	parse_type(char **input, t_token **tokens)
{
	if (**input == '>')
	{
		if (*(*input + 1) == '>')
		{
			add_token_to_list(tokens, new_token(APPEND, ">>"));
			(*input)++;
		}
		else
			add_token_to_list(tokens, new_token(REDIRECT, ">"));
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
		{
			add_token_to_list(tokens, new_token(HEREDOC, "<<"));
			(*input)++;
		}
		else
			add_token_to_list(tokens, new_token(INDIRECT, "<"));
	}
	else if (**input == '|')
		add_token_to_list(tokens, new_token(PIPE, "|"));
	(*input)++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:04:43 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/19 16:27:40 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** Debug Function; dont forgot to comment or delete */
const char	*msh_name_type(t_type type)
{
	switch (type)
	{
	case EMPTY:
		return ("EMPTY");
	case REDIRECT:
		return ("REDIRECT");
	case APPEND:
		return ("APPEND");
	case INDIRECT:
		return ("INDIRECT");
	case HEREDOC:
		return ("HEREDOC");
	case PIPE:
		return ("PIPE");
	case END:
		return ("END");
	case CMD:
		return ("CMD");
	case ARG:
		return ("ARG");
	default:
		return ("UNKNOWN");
	}
}

void	display_tokens(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
	{
		printf("No tokens to display.\n");
		return ;
	}
	printf("%s%-10s | %-10s | %-10s | %-10s %s\n", GREEN, "Input", "Type",
			"Command", "Count Pipe", RESET);
	printf("%s-----------------------------------------------------%s\n", GREEN,
			RESET);
	current = tokens;
	while (current != NULL)
	{
		printf("%-10s | %-10s | %-10s | %-10d\n",
				current->cmd ? current->cmd : "NULL",
				msh_name_type(current->type),
				current->cmd ? current->cmd : "NULL",
				current->count_pipe);
		current = current->next;
	}
	printf("%s-----------------------------------------------------%s\n", GREEN,
			RESET);
}

t_token	*token_input(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	while (*input)
	{
		while (*input && ft_strchr(" \t\n", *input))
			input++;
		if (ft_strchr("><|", *input))
			parse_type(&input, &tokens);
		else
			parse_cmd(&input, &tokens);
	}
	return (tokens);
}

t_token	*msh_parsing_input(char *input)
{
	char	*trimmed_input;
	t_token	*tokens;

	trimmed_input = ft_strtrim(input, " \t\n\v\f\r");
	free(input);
	if (!trimmed_input)
		return (NULL);
	tokens = token_input(trimmed_input);
	free(trimmed_input);
	return (tokens);
}

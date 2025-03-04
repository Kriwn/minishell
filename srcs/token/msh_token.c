/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:04:43 by jikarunw          #+#    #+#             */
/*   Updated: 2025/01/15 23:39:29 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*handle_line(char *input, t_token *current)
// {
// 	if (*input == '\'')
// 		input = handle_single_quote(input, current);
// 	else if (*input == '\"')
// 		input = handle_double_quote(input, current);
// 	else
// 		input = token_word(input, current, WHITESPACE_Q_D);
// 	return (input);
// }

t_token	*token_input(char *input)
{
	t_token	*tokens;
	t_msh	*msh;

	tokens = NULL;
	msh = malloc(sizeof(t_msh));
	if (!msh)
		return (NULL);
	while (*input)
	{
		while (*input && ft_strchr(" \t\n", *input))
			input++;
		if (ft_strchr("><|", *input))
			parse_type(&input, &tokens);
		else
			parse_cmd(&input, &tokens);
	}
	// free(msh);
	return (tokens);
}

t_token	*msh_parsing_input(t_msh *msh)
{
	char	*input_trim;

	input_trim = ft_strtrim(msh->input, WHITESPACE);
	if (syntax_error_checker(input_trim))
	{
		free(input_trim);
		return (NULL);
	}
	if (!input_trim)
		return (NULL);
	msh->token = token_input(input_trim);
	free(input_trim);
	free(msh->input);
	msh_count_pipe(msh);
	return (msh->token);
}

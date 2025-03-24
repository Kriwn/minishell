/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:04:43 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/24 17:12:31 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_token	*msh_parsing_input(t_msh *msh)
{
	char	*input_trim;

	input_trim = ft_strtrim(msh->input, WHITESPACE);
	free(msh->input);
	if (syntax_error_checker(input_trim))
	{
		free(input_trim);
		msh->code = 1;
		return (NULL);
	}
	if (!input_trim)
		return (NULL);
	if (msh->token)
		msh->token = NULL;
	msh->token = token_input(input_trim);
	free(input_trim);
	if (msh->ast)
	{
		free_ast(msh->ast);
		msh->ast = NULL;
	}
	msh_count_pipe(msh);
	return (msh->token);
}

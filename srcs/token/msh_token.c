/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:04:43 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/23 16:14:34 by jikarunw         ###   ########.fr       */
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

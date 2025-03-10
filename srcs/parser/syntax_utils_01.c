/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:55:35 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/08 01:42:14 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_quote_counts(char c, int *s_q_count, int *d_q_count)
{
	if (c == '\'')
		(*s_q_count)++;
	else if (c == '\"')
		(*d_q_count)++;
}

int	is_invalid_operator(const char **input)
{
	if (**input == '>' && *(*input + 1) == '>')
		(*input)++;
	else if (**input == '<' && *(*input + 1) == '<')
		(*input)++;
	else if (**input == '>' || **input == '<')
	{
		(*input)++;
		if (ft_isspace(**input) || !**input)
		{
			ft_putstr_fd("Minishell: syntax error near \
				unexpected token `newline'\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}

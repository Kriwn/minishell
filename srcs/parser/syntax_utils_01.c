/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:55:35 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/13 15:21:59 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_quote_counts(char c, int *s_q_count, int *d_q_count)
{
	if (c == '\'')
		*s_q_count = (*s_q_count + 1) % 2;
	else if (c == '\"')
		*d_q_count = (*d_q_count + 1) % 2;
}

int	is_invalid_operator(const char **input)
{
	if (!input || !*input || !**input)
		return (0);
	if (**input == '>' && *(*input + 1) == '>')
		(*input)++;
	else if (**input == '<' && *(*input + 1) == '<')
		(*input)++;
	else if (**input == '>' || **input == '<')
	{
		(*input)++;
		if (**input == '\0' || ft_isspace(**input))
		{
			ft_putstr_fd("Minishell: syntax error near \
				unexpected token `newline'\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}

void	free_cmd_args(t_ast *cmd_node)
{
	int	i;

	i = 0;
	if (!cmd_node || !cmd_node->args)
		return ;
	while (cmd_node->args[i])
	{
		free(cmd_node->args[i]);
		i++;
	}
	free(cmd_node->args);
	cmd_node->args = NULL;
}

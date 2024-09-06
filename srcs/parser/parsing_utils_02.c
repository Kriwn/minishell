/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:44:48 by jikarunw          #+#    #+#             */
/*   Updated: 2024/09/07 01:39:26 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ph_get_type(t_token *token, int is_delimited)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && is_delimited == 0)
		token->type = REDIRECT;
	else if (ft_strcmp(token->str, ">>") == 0 && is_delimited == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && is_delimited == 0)
		token->type = INDIRECT;
	else if (ft_strcmp(token->str, "<<") == 0 && is_delimited == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, "|") == 0 && is_delimited == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && is_delimited == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= REDIRECT)
		token->type = CMD;
	else
		token->type = ARG;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:44:48 by jikarunw          #+#    #+#             */
/*   Updated: 2024/09/17 14:15:46 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_type msh_get_type(const char *token_str)
{
	if (ft_strcmp(token_str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token_str, ">") == 0)
		return (REDIRECT);
	else if (ft_strcmp(token_str, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(token_str, "<") == 0)
		return (INDIRECT);
	else if (ft_strcmp(token_str, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token_str, ";") == 0)
		return (END);
	else
		return (CMD);
}

/** Debug Function; dont forgot to comment or delete*/
const char *msh_name_type(t_type type)
{
	switch (type)
	{
	case EMPTY:
		return "EMPTY";
	case REDIRECT:
		return "REDIRECT";
	case APPEND:
		return "APPEND";
	case INDIRECT:
		return "INDIRECT";
	case HEREDOC:
		return "HEREDOC";
	case PIPE:
		return "PIPE";
	case END:
		return "END";
	case CMD:
		return "CMD";
	case ARG:
		return "ARG";
	default:
		return "UNKNOWN";
	}
}

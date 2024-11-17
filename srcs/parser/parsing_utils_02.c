/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:44:48 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/17 15:36:18 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*msh_init_token(char *token_str, t_token *prev)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = ft_strdup(token_str);
	new_token->type = msh_get_type(token_str);
	new_token->prev = prev;
	new_token->next = NULL;
	new_token->count = 0;
	new_token->tokens = NULL;
	new_token->cmd = NULL;
	return (new_token);
}

void	msh_check_cmd(t_token *token)
{
	if (token->type == CMD)
		token->cmd = ft_strdup(token->str);
}

t_msh	*init_msh_context(char **envp)
{
	t_msh	*msh;

	msh = malloc(sizeof(t_msh));
	if (!msh)
		return (NULL);
	msh->token = NULL;
	msh->env = envp;
	msh->cwd = getcwd(NULL, 0);
	msh->code = 0;
	return (msh);
}

t_type	msh_get_type(const char *token_str)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:56:36 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/21 21:18:51 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*token_word(char *start, t_token *token, char *delimiter)
// {
// 	char	*cmd;

// 	cmd = msh_strdup_delimiter_string(start, delimiter);
// 	if (!cmd)
// 		return (NULL);
// 	token->cmd = cmd;
// 	token->type = CMD;
// 	start += ft_strlen(cmd);
// 	return (start);
// }

// char	*handle_single_quote(char *start, t_token *token)
// {
// 	char	*cmd;

// 	cmd = msh_strdup_delimiter_char(++start, '\'');
// 	if (!cmd)
// 		return (NULL);
// 	token->cmd = cmd;
// 	token->type = CMD;
// 	start += ft_strlen(cmd) + 1;
// 	return (start);
// }

// char	*handle_double_quote(char *start, t_token *token)
// {
// 	char	*cmd;
// 	char	*dollar;

// 	cmd = msh_strdup_delimiter_char(++start, '\"');
// 	if (!cmd)
// 		return (NULL);
// 	token->cmd = cmd;
// 	dollar = ft_strchr(cmd, '$');
// 	if (dollar && ft_strchr(LETTERS_DIGITS_QM, *(dollar + 1)))
// 		token->type = ENV_VAR;
// 	else
// 		token->type = CMD;
// 	start += ft_strlen(cmd) + 1;
// 	return (start);
// }

void	update_quote_status(char c, int *in_quote, char *quote_char)
{
	if (!*in_quote && (c == '\'' || c == '\"'))
	{
		*in_quote = 1;
		*quote_char = c;
	}
	else if (*in_quote && c == *quote_char)
		*in_quote = 0;
}

void	msh_count_pipe(t_msh *msh)
{
	t_token	*current;
	int		count = 0;

	if (!msh || !msh->token)
	{
		msh->count_pipe = 0;
		return;
	}
	current = msh->token;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	msh->count_pipe = count;
}

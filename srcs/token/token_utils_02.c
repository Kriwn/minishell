/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:56:36 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/25 02:54:19 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int		count;

	count = 0;
	if (!msh || !msh->token)
	{
		msh->count_pipe = 0;
		return ;
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

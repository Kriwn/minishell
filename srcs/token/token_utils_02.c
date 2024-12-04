/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:31:00 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/25 13:21:42 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_token_heredoc(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;
	t_token	*temp;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (prev == NULL)
				*tokens = current->next;
			else
				prev->next = current->next;
			temp = current;
			current = current->next;
			free(temp->cmd);
			free(temp);
			if (current)
			{
				temp = current;
				current = current->next;
				if (prev)
					prev->next = current;
				else
					*tokens = current;
				free(temp->cmd);
				free(temp);
			}
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

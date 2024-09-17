/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/09/17 15:16:39 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *msh_init_token(char *token_str, t_token *prev)
{
	t_token *new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = ft_strdup(token_str);
	new_token->type = msh_get_type(token_str);
	new_token->prev = prev;
	new_token->next = NULL;
	new_token->count = 0;
	new_token->tokens = NULL;
	new_token->cmd = NULL;
	return new_token;
}

void msh_check_cmd(t_token *token)
{
	if (token->type == CMD)
		token->cmd = ft_strdup(token->str);
}

t_token *msh_input(char *input)
{
	t_token *head = NULL;
	t_token *current = NULL;
	t_token *new_token;
	char *token_str = strtok(input, " ");

	while (token_str != NULL)
	{
		new_token = msh_init_token(token_str, current);

		msh_check_cmd(new_token);
		if (head == NULL)
		{
			head = new_token;
			current = head;
		}
		else
		{
			current->next = new_token;
			current = new_token;
		}
		token_str = strtok(NULL, " ");
	}
	return (head);
}

int msh_parsing(char *input)
{
	t_token *tokens = msh_input(input);
	t_token *current = tokens;

	printf("%s%-10s | %-10s | %-10s%s\n", GREEN, "Token", "Type", "Cmd", RESET);
	printf("%s-----------------------------------------%s\n", GREEN, RESET);

	while (current != NULL)
	{
		printf("%-10s | %-10s | %-10s\n", current->str, msh_name_type(current->type), current->cmd ? current->cmd : "NULL");
		current = current->next;
	}
	current = tokens;
	printf("%s-----------------------------------------%s\n", GREEN, RESET);
	while (current != NULL)
	{
		t_token *next = current->next;
		free(current->str);
		free(current->cmd);
		free(current);
		current = next;
	}
	return (0);
}

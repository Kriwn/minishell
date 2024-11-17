/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/17 15:30:11 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*msh_input(char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	char	*token_str;

	head = NULL;
	current = NULL;
	token_str = strtok(input, " ");
	while (token_str != NULL)
	{
		new_token = msh_init_token(token_str, current);
		if (!new_token)
		{
			fprintf(stderr, "Error: Failed to allocate token\n");
			break ;
		}
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

t_token	*msh_parse_tokens(char *input)
{
	t_token	*tokens;
	t_token	*current;

	tokens = msh_input(input);
	current = tokens;
	printf("%s%-10s | %-10s | %-10s%s\n", GREEN, "Token", "Type", "Cmd", RESET);
	printf("%s-----------------------------------------%s\n", GREEN, RESET);
	// Debug: print token show info
	while (current != NULL)
	{
		printf("%-10s | %-10s | %-10s\n",
				current->str,
				msh_name_type(current->type),
				current->cmd ? current->cmd : "NULL");
		current = current->next;
	}
	printf("%s-----------------------------------------%s\n", GREEN, RESET);
	return (tokens);
}

int	msh_execute_commands(t_token *tokens)
{
	t_token	*current;
	t_msh	*msh;
	int		(*builtin_func)(t_msh * msh, t_token * token);

	current = tokens;
	while (current != NULL)
	{
		if (current->type == CMD)
		{
			msh = init_msh_context(NULL);
			if (!msh)
			{
				ft_putstr_fd("Error: Fail init shell context\n", STDERR_FILENO);
				return (-1);
			}
			builtin_func = init_builtin(current->cmd);
			if (builtin_func)
				builtin_func(msh, current);
			free_msh_context(msh);
			break ;
		}
		current = current->next;
	}
	return (0);
}

int	msh_parsing(char *input)
{
	t_token	*tokens;
	t_token	*current;
	t_token	*next;

	tokens = msh_parse_tokens(input);
	current = tokens;
	msh_execute_commands(tokens);
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current->cmd);
		free(current);
		current = next;
	}
	return (0);
}

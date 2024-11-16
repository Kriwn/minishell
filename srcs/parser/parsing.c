/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/16 21:14:47 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*msh_init_token(char *token_str, t_token *prev)
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

void	msh_check_cmd(t_token *token)
{
	if (token->type == CMD)
		token->cmd = ft_strdup(token->str);
}

t_token	*msh_input(char *input)
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

t_msh	*init_msh_context(char **envp)
{
	t_msh *msh = malloc(sizeof(t_msh));
	if (!msh)
		return NULL;

	msh->token = NULL;
	msh->env = envp;
	msh->cwd = getcwd(NULL, 0);
	msh->code = 0;
	return msh;
}

void	free_msh_context(t_msh *msh)
{
	free(msh->cwd);
	free(msh);
}

int	msh_parsing(char *input)
{
	t_token *tokens = msh_input(input);
	t_token *current = tokens;
	int (*builtin_func)(t_msh *msh);

	printf("%s%-10s | %-10s | %-10s%s\n", GREEN, "Token", "Type", "Cmd", RESET);
	printf("%s-----------------------------------------%s\n", GREEN, RESET);
	while (current != NULL)
	{
		printf("%-10s | %-10s | %-10s\n", current->str, msh_name_type(current->type), current->cmd ? current->cmd : "NULL");
		if (current->type == CMD)
		{
			builtin_func = init_builtin(current->str);
			if (builtin_func)
			{
				t_msh *msh = init_msh_context(tokens);
				if (!msh)
					return (ft_putstr_fd("Error: Failed to initialize shell context\n", STDERR_FILENO), -1);

				builtin_func(msh);
				free_msh_context(msh);
				break;
			}
		}
		current = current->next;
	}
	printf("%s-----------------------------------------%s\n", GREEN, RESET);

	// Free token list -> Create function for Norm
	current = tokens;
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

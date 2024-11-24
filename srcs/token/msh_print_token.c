/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_print_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:08:36 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/24 23:44:03 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_token_list(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->cmd);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

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
	case CMD_GROUP:
		return ("CMD_GROUP");
	default:
		return ("UNKNOWN");
	}
}

void	display_tokens(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
	{
		printf("No tokens to display.\n");
		return ;
	}
	printf("%s%-10s | %-10s | %-10s | %-10s %s\n", GREEN, "Input", "Type",
			"Command", "Count Pipe", RESET);
	printf("%s-----------------------------------------------------%s\n", GREEN,
			RESET);
	current = tokens;
	while (current != NULL)
	{
		printf("%-10s | %-10s | %-10s | %-10d\n",
				current->cmd ? current->cmd : "NULL",
				msh_name_type(current->type),
				current->cmd ? current->cmd : "NULL",
				current->count_pipe);
		current = current->next;
	}
	printf("%s-----------------------------------------------------%s\n", GREEN,
			RESET);
}

void	test_delete_heredoc(t_token **tokens)
{
	if (!tokens || !*tokens)
	{
		printf("No tokens to display.\n");
		return ;
	}
	printf("%sBefore delete HEREDOC tokens:%s\n\n", RED, RESET);
	display_tokens(*tokens);
	delete_token_heredoc(tokens);
	printf("%sAfter delete HEREDOC tokens:%s\n\n", YELLOW, RESET);
	display_tokens(*tokens);
}

void	display_ast(t_ast *ast, int idx)
{
	if (!ast)
		return ;
	for (int i = 0; i < idx; i++)
		printf("  ");
	printf("%s(%s)%s\n", GREEN, msh_name_type(ast->type), RESET);
	if (ast->args)
	{
		for (int i = 0; i <= idx; i++)
			printf("  ");
		printf("Command: ");
		for (int i = 0; ast->args[i]; i++)
		{
			printf("%s", ast->args[i]);
			if (ast->args[i + 1])
				printf(" ");
		}
		printf("\n");
	}
	display_ast(ast->left, idx + 1);
	display_ast(ast->right, idx + 1);
}

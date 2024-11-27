/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_print_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:08:36 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/27 19:42:16 by jikarunw         ###   ########.fr       */
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

void	test_delete_heredoc(t_token **tokens)
{
	if (!tokens || !*tokens)
	{
		printf("No tokens to display.\n");
		return ;
	}
	delete_token_heredoc(tokens);
}

void	display_ast_table(t_ast *ast, int level)
{
	if (!ast)
		return;

	if (level == 0)
	{
		printf("%s%-20s | %-15s | %-15s | %-20s | %-20s%s\n",
				GREEN,
				"AST Node Type",
				"Arg",
				"Level",
				"Left Node",
				"Right Node",
				RESET);
		printf("%s---------------------------------------------------------------------------------------------%s\n",
				GREEN, RESET);
	}
	printf("%-20s | %-15s | %-15d | %-20s | %-20s\n",
			msh_name_type(ast->type),
			ast->args ? ast->args[0] : "NULL",
			level,
			ast->left ? msh_name_type(ast->left->type) : "NULL",
			ast->right ? msh_name_type(ast->right->type) : "NULL");
	if (ast->left)
		display_ast_table(ast->left, level + 1);
	if (ast->right)
		display_ast_table(ast->right, level + 1);
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
	printf("\n");
}

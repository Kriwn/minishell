/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_print_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:08:36 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/05 15:40:31 by jikarunw         ###   ########.fr       */
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
	int		pipe_count;

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
				current->type == PIPE ? 1 : 0);
		current = current->next;
	}
	printf("%s-----------------------------------------------------%s\n", GREEN,
			RESET);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:00 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/19 14:06:24 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*msh_init_ast(t_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	msh_free_ast(t_ast *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	if (node->type == CMD && node->args)
	{
		while (node->args && node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	msh_free_ast(node->left);
	msh_free_ast(node->right);
	free(node);
}

t_ast	*create_file_list_redir(t_token **tokens, t_token *tmp)
{
	t_ast	*redirect_node;

	redirect_node = msh_init_ast((*tokens)->type);
	*tokens = (*tokens)->next->next;
	redirect_node->left = msh_get_redirect(tokens);
	redirect_node->right = file_ast_node(tmp->next);
	free(tmp->cmd);
	free(tmp);
	return (redirect_node);
}

int	count_cmd_arg(t_token *current)
{
	int	arg_count;

	arg_count = 0;
	while (current && current->type == CMD)
	{
		arg_count++;
		current = current->next;
	}
	return (arg_count);
}

void	add_cmd_arg(t_ast *cmd_node, t_token **tokens, int arg_count)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (i < arg_count)
	{
		cmd_node->args[i] = ft_strdup((*tokens)->cmd);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->cmd);
		free(tmp);
		i++;
	}
	cmd_node->args[arg_count] = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:00 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/13 19:18:00 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*create_file_list_redir(t_token **tokens, t_token *tmp)
{
	t_ast	*redirect_node;
	t_token	*next;

	redirect_node = msh_init_ast((*tokens)->type);
	if (!redirect_node)
		return (NULL);
	next = (*tokens)->next;
	*tokens = next->next;
	redirect_node->left = msh_get_redirect(tokens);
	redirect_node->right = file_ast_node(next);
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
		if (!cmd_node->args[i])
		{
			while (i > 0)
				free(cmd_node->args[--i]);
			free(cmd_node->args);
			free(cmd_node);
			return ;
		}
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->cmd);
		free_cmd_tokens(&tmp);
		free(tmp);
		i++;
	}
	cmd_node->args[arg_count] = NULL;
}

void	free_cmd_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		if (tmp->cmd)
			free(tmp->cmd);
		free(tmp);
	}
}

void	free_cmd_args(t_ast *cmd_node)
{
	int	i;

	i = 0;
	if (!cmd_node || !cmd_node->args)
		return ;
	while (cmd_node->args[i])
	{
		free(cmd_node->args[i]);
		i++;
	}
	free(cmd_node->args);
	cmd_node->args = NULL;
}

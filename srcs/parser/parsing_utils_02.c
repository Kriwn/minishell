/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:09:32 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/12 08:22:32 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*create_env_var_node(t_token *current)
{
	t_ast	*env_var_node;

	env_var_node = msh_init_ast(ENV_VAR);
	env_var_node->args = malloc(sizeof(char *) * 2);
	if (!env_var_node->args)
		return (NULL);
	env_var_node->args[0] = ft_strdup(current->cmd);
	env_var_node->args[1] = NULL;
	return (env_var_node);
}

void	fill_command_args(t_ast *command_node, t_token *current)
{
	int	i;

	i = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == ENV_VAR)
			command_node->left = create_env_var_node(current);
		else
			command_node->args[i++] = ft_strdup(current->cmd);
		current = current->next;
	}
	command_node->args[i] = NULL;
}

t_ast	*create_pipe_node(t_token **tokens, t_token *tmp, t_token *next_token)
{
	t_ast	*pipe_node;
	t_ast	*command_group;

	pipe_node = msh_init_ast(next_token->type);
	(*tokens)->next = NULL;
	command_group = msh_init_ast(CMD_GROUP);
	command_group->left = msh_get_redirect(&tmp);
	pipe_node->left = command_group;
	pipe_node->right = msh_get_pipe(&(next_token->next));
	free(next_token->cmd);
	free(next_token);
	return (pipe_node);
}

int	allocate_cmd_args(t_ast *cmd_node, int arg_count)
{
	cmd_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd_node->args)
	{
		free(cmd_node);
		return (0);
	}
	return (1);
}

void	copy_command_args(t_ast *command_node, t_token **tokens)
{
	t_token	*current;
	int		i;

	current = *tokens;
	i = 0;
	while (current && current->type == CMD)
	{
		command_node->args[i] = ft_strdup(current->cmd);
		if (!command_node->args[i])
		{
			while (--i >= 0)
				free(command_node->args[i]);
			free(command_node->args);
			command_node->args = NULL;
			return ;
		}
		i++;
		current = current->next;
	}
	command_node->args[i] = NULL;
}

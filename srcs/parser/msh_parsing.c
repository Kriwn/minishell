/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/24 17:40:35 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	allocate_cmd_args(t_ast *command_node, int arg_count)
{
	if (!command_node)
		return (0);
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->args)
	{
		free(command_node);
		return (0);
	}
	return (1);
}

int	copy_command_args(t_ast *command_node, t_token **tokens)
{
	int		i;
	t_token	*current;

	i = 0;
	current = *tokens;
	if (!command_node || !command_node->args)
		return (0);
	while (current && current->type == CMD)
	{
		command_node->args[i] = ft_strdup(current->cmd);
		if (!command_node->args[i])
		{
			while (i > 0)
				free(command_node->args[--i]);
			free(command_node->args);
			command_node->args = NULL;
			return (0);
		}
		i++;
		current = current->next;
	}
	command_node->args[i] = NULL;
	return (1);
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

t_ast	*msh_get_cmd(t_token **tokens)
{
	t_ast	*command_node;
	int		arg_count;

	if (!tokens || !*tokens)
		return (NULL);
	command_node = msh_init_ast(CMD);
	if (!command_node)
		return (NULL);
	arg_count = count_cmd_arg(*tokens);
	if (!allocate_cmd_args(command_node, arg_count))
	{
		free(command_node);
		return (NULL);
	}
	if (!copy_command_args(command_node, tokens))
	{
		free_cmd_args(command_node);
		free_cmd_tokens(tokens);
		free(command_node);
		return (NULL);
	}
	free_cmd_tokens(tokens);
	return (command_node);
}

t_ast	*msh_get_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if (!validate_tokens(*tokens))
		return (NULL);
	return (msh_get_pipe(tokens));
}

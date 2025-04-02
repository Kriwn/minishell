/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2025/04/02 20:49:47 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*msh_get_cmd(t_token **tokens)
{
	t_ast	*cmd_node;

	if (!tokens || !*tokens)
		return (NULL);
	cmd_node = msh_init_ast(CMD);
	if (!cmd_node)
		return (NULL);
	if (!init_cmd_node_args(cmd_node, tokens))
	{
		free(cmd_node);
		return (NULL);
	}
	if (*tokens && (*tokens)->type == HEREDOC)
	{
		if (!handle_heredoc(tokens, cmd_node))
		{
			cleanup_cmd_node(cmd_node);
			return (NULL);
		}
	}
	return (cmd_node);
}

t_ast	*msh_get_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if (!validate_tokens(*tokens))
		return (NULL);
	return (msh_get_pipe(tokens));
}

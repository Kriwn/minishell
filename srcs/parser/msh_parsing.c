/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2025/04/02 22:47:14 by jikarunw         ###   ########.fr       */
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
	if (!init_cmd_args(cmd_node, tokens) || !copy_cmd_args(cmd_node, tokens))
	{
		cleanup_cmd_node(cmd_node);
		return (NULL);
	}
	process_heredoc_if_needed(tokens, cmd_node);
	// free(*tokens);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:09:32 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/25 03:38:40 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*msh_get_heredoc_word(t_token **token)
{
	t_ast	*heredoc_node;
	t_ast	*heredoc_word_node;
	t_ast	*next_heredoc_node;

	if (!token || !*token || (*token)->type != HEREDOC)
		return (NULL);
	heredoc_node = msh_init_ast(HEREDOC);
	if (!heredoc_node)
		return (NULL);
	*token = (*token)->next;
	if (!*token || (*token)->type != CMD)
	{
		free(heredoc_node);
		return (NULL);
	}
	heredoc_word_node = msh_init_ast(HEREDOC_WORD);
	if (!heredoc_word_node)
	{
		free(heredoc_node);
		return (NULL);
	}
	heredoc_word_node->args = malloc(sizeof(char *) * 2);
	if (!heredoc_word_node->args)
	{
		free(heredoc_node);
		free(heredoc_word_node);
		return (NULL);
	}
	heredoc_word_node->args[0] = ft_strdup((*token)->cmd);
	heredoc_word_node->args[1] = NULL;
	heredoc_node->right = heredoc_word_node;
	t_token *next_token = (*token)->next;
	free((*token)->cmd);
	free(*token);
	*token = next_token;
	if (*token && (*token)->type == HEREDOC)
	{
		next_heredoc_node = msh_get_heredoc_word(token);
		heredoc_node->left = next_heredoc_node;
	}
	return (heredoc_node);
}

// t_ast	*msh_get_cmd(t_token **tokens)
// {
// 	t_ast	*command_node;
// 	int		arg_count;

// 	command_node = msh_init_ast(CMD);
// 	arg_count = count_cmd_arg(*tokens);
// 	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
// 	if (!command_node->args)
// 		return (NULL);
// 	add_cmd_arg(command_node, tokens, arg_count);
// 	return (command_node);
// }

t_ast	*msh_get_cmd(t_token **tokens)
{
	t_ast	*command_node;
	int		arg_count;
	t_token	*current;

	command_node = msh_init_ast(CMD);
	arg_count = count_cmd_arg(*tokens);
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->args)
		return (NULL);
	current = *tokens;
	int i = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == ENV_VAR)
		{
			t_ast *env_var_node = msh_init_ast(ENV_VAR);
			env_var_node->args = malloc(sizeof(char *) * 2);
			if (!env_var_node->args)
				return (NULL);
			env_var_node->args[0] = ft_strdup(current->cmd);
			env_var_node->args[1] = NULL;
			command_node->left = env_var_node;
		}
		else
			command_node->args[i++] = ft_strdup(current->cmd);
		current = current->next;
	}
	command_node->args[i] = NULL;
	return (command_node);
}


t_ast	*msh_get_redirect(t_token **tokens)
{
	t_token	*tmp;
	t_ast	*redirect_node;
	t_token	*next_token;

	if (!*tokens)
		return (NULL);
	tmp = *tokens;
	if ((*tokens)->type >= INDIRECT && (*tokens)->type <= HEREDOC)
	{
		if ((*tokens)->type == HEREDOC)
			return (msh_get_heredoc_word(tokens));
		return (create_file_list_redir(tokens, tmp));
	}
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type >= INDIRECT && (*tokens)->next->type <= HEREDOC)
		{
			if (next_token->type == HEREDOC)
			{
				redirect_node = msh_init_ast(HEREDOC);
				(*tokens)->next = next_token->next->next;
				redirect_node->left = msh_get_redirect(&tmp);
				redirect_node->right = msh_get_heredoc_word(&next_token->next);
				return (redirect_node);
			}
			redirect_node = msh_init_ast((*tokens)->next->type);
			(*tokens)->next = next_token->next->next;
			redirect_node->left = msh_get_redirect(&tmp);
			redirect_node->right = file_ast_node((next_token->next));
			return (free(next_token->cmd), free(next_token), redirect_node);
		}
		*tokens = next_token;
	}
	return (msh_get_cmd(&tmp));
}

t_ast	*msh_get_pipe(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next_token;
	t_ast	*pipe_node;
	t_ast	*command_group;

	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if (next_token->type == PIPE)
		{
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
		*tokens = next_token;
	}
	command_group = msh_init_ast(CMD_GROUP);
	command_group->left = msh_get_redirect(&tmp);
	return (command_group);
}

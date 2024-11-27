/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/27 18:56:13 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*file_ast_node(t_token *token)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = token->cmd;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	free(token);
	return (node);
}

t_ast	*msh_get_cmd(t_token **tokens)
{
	t_ast	*command_node;
	int		arg_count;

	command_node = msh_init_ast(CMD);
	arg_count = count_cmd_arg(*tokens);
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->args)
		return (NULL);
	add_cmd_arg(command_node, tokens, arg_count);
	command_node->builtin = init_builtin(command_node->args[0]);
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
	if ((*tokens)->type >= REDIRECT && (*tokens)->type <= HEREDOC)
		return (create_file_list_redir(tokens, tmp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type >= REDIRECT
			&& (*tokens)->next->type <= HEREDOC)
		{
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

t_ast	*msh_get_tokens(t_token **tokens)
{
	t_msh	*msh;

	if (!tokens || !*tokens)
		return (NULL);
	// display_tokens(*tokens);
	// test_delete_heredoc(tokens);
	return (msh_get_pipe(tokens));
}

/**
 * @brief Execute the abstract syntax tree : Test function
 * @jikarunw
 */

char	*heredoc_ast(t_ast *ast, t_msh *msh)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return (NULL);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, ast->args[0]))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open("/tmp/heredoc", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (NULL);
	}
	tmp = ft_strdup("/tmp/heredoc");
	free(ast->args[0]);
	ast->args[0] = tmp;
	return (tmp);
}

int	execute_ast(t_ast *ast, t_msh *msh)
{
	pid_t	pid;
	int		status;

	if (!ast)
		return (1);
	if (ast->type == CMD && ast->builtin)
		return (ast->builtin(msh));
	if (ast->type == PIPE)
	{
		execute_ast(ast->left, msh);
		execute_ast(ast->right, msh);
		return (0);
	}
	if (ast->type == CMD)
	{
		pid = fork();
		if (pid == 0)
		{
			execvp(ast->args[0], ast->args);
			perror("execvp");
			msh->code = 1;
			free(ast->args[0]);
			exit(1);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			msh->code = 0;
			return (WEXITSTATUS(status));
		}
		else
		{
			perror("fork");
			msh->code = 1;
			return (1);
		}
	}
	execute_ast(ast->left, msh);
	execute_ast(ast->right, msh);
	// printf("%s---------------------------------------------------------------------------------------------%s\n",
	// 		GREEN, RESET);
	return (0);
}

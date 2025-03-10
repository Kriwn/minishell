/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:31:29 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/10 11:20:54 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_ast(t_ast *node)
{
	int	i;

	i = 0;
	if (!node)
		return;
	if (node->args && node->type == CMD)
	{
		while (node->args[i])
			free(node->args[i++]);
		free(node->args);
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

void free_token(t_token *tokens)
{
	t_token *tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->cmd)
		{
			free(tokens->cmd);
			tokens->cmd = NULL;
		}
		free(tokens);
		tokens = tmp;
	}
	tokens = NULL;
}


void	ft_free(t_msh *data)
{
	data->home_path = NULL;
	clear_tuple(&data->tuple);
	free(data->list);
	free(data);
}

void	ft_error(t_msh *data, char *word)
{
	ft_putstr_fd(word, 2);
	ft_free(data);
	exit(EXIT_FAILURE);
}

void	cleanup_and_exit(t_msh *msh, int exit_code)
{
	if (msh->token)
		free_token(msh->token);
	if (msh->ast)
		free_ast(msh->ast);
	if (msh->input)
		free(msh->input);
	free(msh);
	rl_clear_history();
	exit(exit_code);
}

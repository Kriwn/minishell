/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:31:29 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/17 20:38:13 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (!token || !*token) 
		return;
	current = *token;
	while (current)
	{
		next = current->next;
		if (current->cmd)
		{
			free(current->cmd);
			current->cmd = NULL;
		}
		free(current);
		current = next;
	}
	*token = NULL;
}

void	free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			node->args[i] = NULL;
			i++;
		}
		free(node->args);
		node->args = NULL;
	}
	free_ast(node->left);
	node->left = NULL;
	free_ast(node->right);
	node->right = NULL;
	free(node);
}

void	clean_up_token(t_token **tokens)
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

void	ft_free(t_msh *data)
{
	data->home_path = NULL;
	clear_tuple(&data->tuple);
	if (data->list)
	{
		free(data->list);
	}
	if (data)
		free(data);
}

void	cleanup_and_exit(t_msh *msh, int exit_code)
{
	if (!msh)
		exit(exit_code);
	if (msh->ast)
		free_ast(msh->ast);
	clear_tuple(&msh->tuple);
	if (msh->list)
		free(msh->list);
	free(msh);
	exit(exit_code);
}

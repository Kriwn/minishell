/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:31:29 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/13 15:19:45 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_ast *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
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

void	ft_error(t_msh *data, char *word)
{
	ft_putstr_fd(word, 2);
	ft_free(data);
	exit(EXIT_FAILURE);
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

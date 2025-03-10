/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:31:29 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/10 08:37:08 by jikarunw         ###   ########.fr       */
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
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->cmd);
		free(tmp);
	}
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

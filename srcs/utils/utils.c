/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:31:29 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/28 02:59:53 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->args)
	{
		free(ast->args[0]);
		free(ast->args);
	}
	free(ast);
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

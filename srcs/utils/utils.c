/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:31:29 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/24 02:22:37 by jikarunw         ###   ########.fr       */
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
}

void	ft_error(t_msh *data, char *word)
{
	ft_putstr_fd(word, 2);
	ft_free(data);
	exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:00 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/16 21:20:18 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *err)
{
	t_msh *msh;

	msh->code = 2;
	printf("syntax error near unexpected token `%s'\n", err);
}

void	free_split_result(char **result)
{
	char **temp = result;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(result);
}

void	free_token(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return;
	if (token->tokens)
	{
		while (token->tokens[i++])
			free(token->tokens[i]);
		free(token->tokens);
	}
	free(token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:00 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/17 15:30:44 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_msh_context(t_msh *msh)
{
	free(msh->cwd);
	free(msh);
}

void	free_split_result(char **result)
{
	char	**temp;

	temp = result;
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
		return ;
	if (token->tokens)
	{
		while (token->tokens[i++])
			free(token->tokens[i]);
		free(token->tokens);
	}
	free(token);
}

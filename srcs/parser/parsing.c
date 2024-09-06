/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/09/07 01:47:43 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *msh_input(char *input)
{
	t_token	*token;
	char	**split_tokens;
	int		i;

	i = 0;
	if (!input)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	split_tokens = msh_split(input, "|&<>");
	if (!split_tokens)
	{
		free(token);
		return (NULL);
	}
	while (split_tokens[i])
		i++;
	token->count = i;
	token->tokens = malloc((i + 1) * sizeof(char *));
	if (!token->tokens)
	{
		free_split_result(split_tokens);
		free(token);
		return (NULL);
	}
	i = 0;
	while (split_tokens[i])
	{
		token->tokens[i] = ft_strdup(split_tokens[i]);
		if (!token->tokens[i])
		{
			while (i-- > 0)
				free(token->tokens[i]);
			free(token->tokens);
			free_split_result(split_tokens);
			free(token);
			return (NULL);
		}
		i++;
	}
	token->tokens[i] = NULL;
	free_split_result(split_tokens);
	return (token);
}

int msh_parsing(char *input)
{
	t_token	*token;
	int		i;

	i = 0;
	if (!input)
		return (-1);
	token = msh_input(input);
	if (!token)
		return (-1);
	while (i < token->count)
	{
		printf("token print[%d]: %s\n", i, token->tokens[i]);
		i++;
	}
	free_token(token);
	return (0);
}

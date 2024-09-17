/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:29:53 by jikarunw          #+#    #+#             */
/*   Updated: 2024/09/07 02:26:52 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_tokens(const char *str, const char *symbol)
{
	int count = 0;
	int in_token = 0;
	int in_quotes = 0;

	while (*str)
	{
		if (*str == '"')
		{
			in_quotes = !in_quotes;
			str++;
			continue;
		}
		if (in_quotes || (!ft_strchr(symbol, *str) && !ft_isspace(*str)))
		{
			if (!in_token)
			{
				in_token = 1;
				count++;
			}
		}
		else if (in_token)
			in_token = 0;
		str++;
	}
	return count;
}

static char *copy_token(const char **str, const char *symbol)
{
	const char *start = *str;
	int in_quotes = 0;

	while (**str && (in_quotes || (!ft_strchr(symbol, **str) && !ft_isspace(**str))))
	{
		if (**str == '"')
			in_quotes = !in_quotes;
		(*str)++;
	}
	return ft_strndup(start, *str - start);
}

t_token *msh_split(char *str, const char *symbol)
{
	t_token *result = malloc(sizeof(t_token));
	char *current_str = str;
	int i = 0;

	if (!result)
		return NULL;
	result->count = count_tokens(str, symbol);
	result->tokens = malloc((result->count + 1) * sizeof(char *));
	if (!result->tokens)
	{
		free(result);
		return NULL;
	}
	while (i < result->count)
	{
		while (*current_str && (ft_isspace(*current_str) || ft_strchr(symbol, *current_str)))
			current_str++;
		result->tokens[i] = copy_token((const char **)&current_str, symbol);
		if (!result->tokens[i])
		{
			while (i-- > 0)
				free(result->tokens[i]);
			free(result->tokens);
			free(result);
			return NULL;
		}
		i++;
	}
	result->tokens[result->count] = NULL;
	return result;
}

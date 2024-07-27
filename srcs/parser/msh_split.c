/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:29:53 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/28 01:09:31 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_tokens(const char *str, const char *symbol)
{
	int	count = 0;
	int	in_token = 0;
	int	in_quotes = 0;

	while (*str)
	{
		if (*str == '"')
		{
			in_quotes = !in_quotes;
			str++;
			continue ;
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
	return (count);
}

static char *copy_token(const char **str, const char *symbol)
{
	const char	*start = *str;
	int			in_quotes = 0;

	while (**str && (in_quotes || (!ft_strchr(symbol, **str) && !ft_isspace(**str))))
	{
		if (**str == '"')
			in_quotes = !in_quotes;
		(*str)++;
	}
	return (ft_strndup(start, *str - start));
}

char **msh_split(char *str, const char *symbol)
{
	int		token_count = count_tokens(str, symbol);
	char	**result = malloc((token_count + 1) * sizeof(char *));
	char	*current_str = str;
	int		i = 0;

	if (!result)
		return (NULL);
	while (i < token_count)
	{
		while (*current_str && (ft_isspace(*current_str) || ft_strchr(symbol, *current_str)))
			current_str++;
		result[i] = copy_token((const char **)&current_str, symbol);
		if (!result[i])
		{
			while (i-- > 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[token_count] = NULL;
	return (result);
}

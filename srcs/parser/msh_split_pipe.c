/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:29:53 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/26 20:04:07 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_splits(char *str, char c)
{
	bool	in_squote;
	bool	in_dquote;
	int		count;
	int		i;

	in_dquote = false;
	in_dquote = false;
	count = 0;
	i = 0;
	while (str[i++])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == c && !in_squote && !in_dquote)
			count++;
	}
	return (count + 1);
}

static char	*substr_dup(const char *str, int start, int end)
{
	char	*sub;
	int		i;
	
	i = 0;
	sub = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!sub)
		return (NULL);
	while (start < end)
		sub[i++] = str[start++];
	sub[i] = '\0';
	return (sub);
}

char	**msh_split_pipe(char *str, char c)
{
	int		num_splits;
	int		start;
	int		end;
	int		idx;
	bool	in_squote;
	bool	in_dquote;
	char	**splits;
	int		i;

	start = 0;
	end = 0;
	idx = 0;
	in_dquote = false;
	in_squote = false;
	num_splits = count_splits(str, c);
	i = 0;
	splits = (char **)malloc(sizeof(char *) * (num_splits + 1));
	if (!splits)
		return (NULL);
	while (str[i++])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == c && !in_squote && !in_dquote)
		{
			splits[idx++] = substr_dup(str, start, i);
			start = i + 1;
		}
	}
	splits[idx++] = substr_dup(str, start, i);
	splits[idx] = NULL;
	return (splits);
}

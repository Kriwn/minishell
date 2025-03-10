/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:40:03 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/03 16:54:39 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freeall(char ***ptr)
{
	size_t	i;

	i = 0;
	while ((*ptr)[i])
	{
		free((*ptr)[i]);
		i++;
	}
	free(*ptr);
	*ptr = NULL;
}

size_t	count(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

int	makearray(char **ptr, char const *s, char c)
{
	size_t	start;
	size_t	len;
	size_t	i;

	start = 0;
	len = 0;
	i = 0;
	while (i < count(s, c))
	{
		while (s[start] == c)
			start++;
		while (s[start + len] != '\0' && s[start + len] != c)
			len++;
		ptr[i] = ft_substr(s, start, len);
		if (!ptr[i])
		{
			freeall(&ptr);
			return (1);
		}
		start += len;
		len = 0;
		i++;
	}
	ptr[i] = NULL;
	return (0);
}

char	**myft_split(char const *s, char c)
{
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = malloc(sizeof(char *) * (count(s, c) + 1));
	if (!ptr)
		return (NULL);
	if (makearray(ptr, s, c))
		return (NULL);
	return (ptr);
}

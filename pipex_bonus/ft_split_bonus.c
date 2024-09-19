/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:56:53 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/14 12:55:13 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
			return (1);
		start += len;
		len = 0;
		i++;
	}
	ptr[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
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

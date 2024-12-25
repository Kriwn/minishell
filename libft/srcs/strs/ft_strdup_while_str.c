/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_while_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 23:11:18 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/23 23:11:33 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup_while_string(char *str, char *charset)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i] && ft_strchr(charset, str[i]))
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, str, i + 1);
	return (dup);
}

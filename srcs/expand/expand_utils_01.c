/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:03:55 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/07 02:01:38 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_single_quotes(char **str)
{
	char	*segment;
	char	*end;

	(*str)++;
	end = ft_strchr(*str, '\'');
	if (!end)
		end = *str + ft_strlen(*str);
	segment = ft_substr(*str, 0, end - *str);
	if (*end == '\'')
		*str = end + 1;
	else
		*str = end;
	return (segment);
}

char	*handle_double_quotes(t_msh *shell, char **str)
{
	char	*segment;
	char	*expanded;
	char	*end;

	(*str)++;
	end = ft_strchr(*str, '"');
	if (!end)
		end = *str + ft_strlen(*str);
	segment = ft_substr(*str, 0, end - *str);
	expanded = expand_string(shell, segment, 1);
	free(segment);
	if (*end == '"')
		*str = end + 1;
	else
		*str = end;
	return (expanded);
}

char	*handle_plain_text(char **str)
{
	int		len;
	char	*segment;

	len = 0;
	while ((*str)[len] && (*str)[len] != '$' && (*str)[len] != '\''
		&& (*str)[len] != '"')
		len++;
	segment = ft_substr(*str, 0, len);
	*str += len;
	return (segment);
}

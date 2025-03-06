/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:16:53 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/07 01:38:41 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_string(t_msh *shell, char *str, int expand_vars)
{
	char	*result;
	char	*temp;
	char	*segment;
	char	*end;

	result = ft_strdup("");
	while (*str)
	{
		segment = NULL;
		if (*str == '\'')
		{
			str++;
			end = ft_strchr(str, '\'');
			if (!end)
				end = str + ft_strlen(str);
			segment = ft_substr(str, 0, end - str);
			str = (*end == '\'') ? end + 1 : end;
		}
		else if (*str == '"')
		{
			str++;
			end = ft_strchr(str, '"');
			if (!end)
				end = str + ft_strlen(str);
			segment = expand_string(shell, ft_substr(str, 0, end - str), 1);
			str = (*end == '"') ? end + 1 : end;
		}
		else if (*str == '$' && expand_vars)
			segment = extract_variable_value(shell, &str);
		else
		{
			int len = 0;
			while (str[len] && str[len] != '$' && str[len] != '\'' && str[len] != '"')
				len++;
			segment = ft_substr(str, 0, len);
			str += len;
		}
		if (segment)
		{
			temp = result;
			result = ft_strjoin(result, segment);
		}
	}
	return (result);
}

void	process_expansion(t_msh *shell)
{
	t_token	*current;
	char	*expanded_cmd;

	current = shell->token;
	while (current)
	{
		if (ft_strchr(current->cmd, '$') || ft_strchr(current->cmd, '"') || ft_strchr(current->cmd, '\''))
		{
			expanded_cmd = expand_string(shell, current->cmd, 1);
			free(current->cmd);
			current->cmd = expanded_cmd;
		}
		current = current->next;
	}
}

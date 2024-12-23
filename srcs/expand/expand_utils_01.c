/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:03:55 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/23 23:11:27 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fetch_environment_value(t_msh *shell, char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0)
		{
			if (shell->env[i][key_len] == '=')
				return (ft_strdup(ft_strchr(shell->env[i], '=') + 1));
		}
		i++;
	}
	return (NULL);
}

char	*get_variable_value(t_msh *shell, char *key)
{
	char	*env_value;

	if (*key == '$')
		return ("$$");
	env_value = fetch_environment_value(shell, key);
	if (!env_value)
		env_value = ft_strdup("");
	return (env_value);
}

char	*locate_variable_reference(char *str)
{
	while (*str)
	{
		if (*str == '$' && *(str + 1) && !ft_strchr(WHITESPACE, *(str + 1)))
			return (str);
		str++;
	}
	return (NULL);
}

char	*duplicate_until_variable(char *str)
{
	int		len;
	char	*dup;
	char	*variable_start;

	if (!str)
		return (NULL);
	variable_start = locate_variable_reference(str);
	if (variable_start == NULL)
		return (str);
	len = variable_start - str;
	if (len < 1)
		return (NULL);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	ft_strncpy(dup, str, len);
	dup[len] = '\0';
	return (dup);
}

void	free_multiple_strings(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

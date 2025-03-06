/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:03:55 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/07 01:38:51 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_msh *shell, char *key)
{
	int		i;
	int		key_len;
	char	*env_value;

	if (!key || !shell->env)
		return (ft_strdup(""));
	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(shell->code));
	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0 && shell->env[i][key_len] == '=')
		{
			env_value = ft_strdup(shell->env[i] + key_len + 1);
			return (env_value);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*extract_variable_value(t_msh *shell, char **str)
{
	char	*var_name;
	char	*expanded_value;

	(*str)++;
	if (**str == '?')
	{
		expanded_value = ft_itoa(shell->code);
		(*str)++;
		return (expanded_value);
	}
	var_name = ft_strdup_while_string(*str, LETTERS_DIGITS);
	if (!var_name || ft_strlen(var_name) == 0)
	{
		free(var_name);
		return (ft_strdup("$"));
	}
	expanded_value = get_env_value(shell, var_name);
	free(var_name);
	(*str) += ft_strlen(var_name);
	return (expanded_value);
}

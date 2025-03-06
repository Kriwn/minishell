/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:16:53 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/06 10:48:15 by jikarunw         ###   ########.fr       */
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
	if (ft_strcmp(key, "$$") == 0)
		return (ft_itoa(getpid()));
	if (ft_strcmp(key, "$?") == 0)
		return (ft_itoa(shell->code));
	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
		{
			env_value = ft_strdup(ft_strchr(shell->env[i], '=') + 1);
			return (env_value);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*expand_variable(t_msh *shell, char *str)
{
	char	*result;
	char	*prefix;
	char	*variable;
	char	*expanded_value;

	if (!str || !ft_strchr(str, '$'))
		return (ft_strdup(str));

	result = ft_strdup("");
	while (*str)
	{
		if (*str == '\'')
		{
			char *quoted_part = extract_single_quote(&str);
			result = ft_strjoin(result, quoted_part);
			continue;
		}
		else if (*str == '"')
		{
			char *quoted_part = extract_double_quote(&str, shell);
			result = ft_strjoin(result, quoted_part);
			continue;
		}
		prefix = duplicate_until_variable(str);
		str = locate_variable_reference(str);
		if (!str)
		{
			result = ft_strjoin(result, prefix);
			break ;
		}
		variable = ft_strdup_while_string(++str, LETTERS_DIGITS);
		if (ft_strchr(variable, '?') == 0)
			expanded_value = ft_itoa(shell->code);
		else
			expanded_value = get_env_value(shell, variable);
		prefix = ft_strjoin(prefix, expanded_value);
		str += ft_strlen(variable);
		result = ft_strjoin(result, prefix);
		free(variable);
	}
	return (result);
}

void	process_expansion(t_msh *shell)
{
	t_token	*current;
	char	*temp;

	current = shell->token;
	while (current)
	{
		if (ft_strchr(current->cmd, '$'))
		{
			temp = current->cmd;
			current->cmd = expand_variable(shell, temp);
			free(temp);
		}
		current = current->next;
	}
}

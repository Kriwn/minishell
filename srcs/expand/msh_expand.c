/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:36:37 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/10 23:19:01 by jikarunw         ###   ########.fr       */
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
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
		{
			env_value = ft_strdup(shell->env[i] + key_len + 1);
			return (env_value);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*expand_variable_value(t_msh *shell, char **str)
{
	char	*expanded_value;
	char	*result;

	(*str)++;
	expanded_value = get_special_variable_value(shell, str);
	if (expanded_value)
	{
		result = ft_strdup(expanded_value);
		free(expanded_value);
		return (result);
	}
	return (get_normal_variable_value(shell, str));
}

char	*process_segment(t_msh *shell, char **str, int expand_vars)
{
	if (**str == '\'')
		return (handle_single_quotes(str));
	else if (**str == '"')
		return (handle_double_quotes(shell, str));
	else if (**str == '$' && expand_vars)
		return (expand_variable_value(shell, str));
	else
		return (handle_plain_text(str));
}

char	*expand_string(t_msh *shell, char *str, int expand_vars)
{
	char	*result;
	char	*temp;
	char	*segment;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (*str)
	{
		segment = process_segment(shell, &str, expand_vars);
		if (segment)
		{
			temp = result;
			result = ft_strjoin_for_other(result, segment);
			free(temp);
			free(segment);
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
		if (ft_strchr(current->cmd, '$') || ft_strchr(current->cmd, '"')
			|| ft_strchr(current->cmd, '\''))
		{
			expanded_cmd = expand_string(shell, current->cmd, 1);
			free(current->cmd);
			current->cmd = expanded_cmd;
		}
		current = current->next;
	}
}

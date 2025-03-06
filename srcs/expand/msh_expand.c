/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:16:53 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/07 02:43:07 by jikarunw         ###   ########.fr       */
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
	else if (**str == '$')
	{
		expanded_value = ft_itoa(getpid());
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

char	*process_segment(t_msh *shell, char **str, int expand_vars)
{
	if (**str == '\'')
		return (handle_single_quotes(str));
	else if (**str == '"')
		return (handle_double_quotes(shell, str));
	else if (**str == '$' && expand_vars)
		return (extract_variable_value(shell, str));
	else
		return (handle_plain_text(str));
}

char	*expand_string(t_msh *shell, char *str, int expand_vars)
{
	char	*result;
	char	*temp;
	char	*segment;

	result = ft_strdup("");
	while (*str)
	{
		segment = process_segment(shell, &str, expand_vars);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:16:53 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/24 01:18:51 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_variables(t_msh *shell, char *original_str)
{
	char	*prefix;
	char	*variable;
	char	*result;
	char	*env_value;

	if (!original_str)
		return (NULL);
	result = ft_strdup("");
	while (*original_str)
	{
		prefix = duplicate_until_variable(original_str);
		original_str = locate_variable_reference(original_str);
		if (!original_str)
		{
			result = ft_strjoin(result, prefix);
			break ;
		}
		variable = ft_strdup_while_string(++original_str, LETTERS_DIGITS);
		env_value = get_variable_value(shell, variable);
		prefix = ft_strjoin(prefix, env_value);
		original_str += ft_strlen(variable);
		result = ft_strjoin(result, prefix);
		free_multiple_strings(prefix, variable, env_value);
	}
	return (result);
}

void	replace_status_with_value(t_msh *shell, t_token *current)
{
	free(current->cmd);
	current->cmd = ft_itoa(shell->code);
}

void	replace_exit_status(char *original, char *replacement, char *exit_code)
{
	int	i;
	int	j;

	i = 0, j = 0;
	while (original[i] != '$')
	{
		replacement[i] = original[i];
		i++;
	}
	while (exit_code[j])
	{
		replacement[i + j] = exit_code[j];
		j++;
	}
	while (original[i + 2])
	{
		replacement[i + j] = original[i + 2];
		i++;
	}
	replacement[i + j] = '\0';
}

void	expand_exit_code(t_msh *shell, t_token *current)
{
	char	*original;
	char	*exit_code;
	char	*replacement;

	original = current->cmd;
	if (!original)
		return ;
	if (!ft_strnstr(original, "$?", ft_strlen(original)))
		return ;
	exit_code = ft_itoa(shell->code);
	replacement = malloc(ft_strlen(original) - 1 + ft_strlen(exit_code));
	if (!replacement)
		return ;
	replace_exit_status(original, replacement, exit_code);
	free(current->cmd);
	free(exit_code);
	current->cmd = replacement;
}

char *msh_expand_variable(t_msh *shell, char *token_value)
{
	if (ft_strncmp(token_value, "$?", 2) == 0)
		return (ft_itoa(shell->code));
	return (ft_strdup(token_value));
}

void	process_expansion(t_msh *shell)
{
	t_token	*current;
	char	*temp;

	current = shell->token;
	while (current)
	{
		if (current->type == ENV_VAR)
		{
			if (current->prev && current->prev->type == HEREDOC)
			{
				temp = current->cmd;
				current->cmd = expand_variables(shell, temp);
				free(temp);
			}
			else if (current->cmd[0] == '$' && current->cmd[1] == '?')
				replace_status_with_value(shell, current);
			else if (current->cmd[0] == '$' && current->cmd[1] == '$')
			{
				expand_exit_code(shell, current);
				temp = current->cmd;
				current->cmd = expand_variables(shell, temp);
				free(temp);
			}
			else if (!ft_strcmp(current->cmd, "$?"))
				replace_status_with_value(shell, current);
			else if (ft_strcmp(current->cmd, "$$"))
			{
				expand_exit_code(shell, current);
				temp = current->cmd;
				current->cmd = expand_variables(shell, temp);
				free(temp);
			}
		}
		current = current->next;
	}
}

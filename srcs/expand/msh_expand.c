/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:16:53 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/24 03:17:20 by jikarunw         ###   ########.fr       */
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
		printf("Test Expand!");
		current = current->next;
	}
}

char *msh_expand_variable(t_msh *shell, char *token_value)
{
	if (ft_strncmp(token_value, "$?", 2) == 0)
		return (ft_itoa(shell->code));
	return (ft_strdup(token_value));
}

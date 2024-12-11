/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:16:53 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/09 09:15:18 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_strdup_while_string(const char *s, char *delimiter)
{
	int		i;
	char	*dup;

	i = 0;
	while (s[i] && ft_strchr(delimiter, s[i]))
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[i] && ft_strchr(delimiter, s[i]))
	{
		((unsigned char *)dup)[i] = ((unsigned char *)s)[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		tlenght;
	char	*n_str;

	i = 0;
	j = 0;
	tlenght = ft_strlen(s1) + ft_strlen(s2) + 1;
	n_str = (char *)malloc(sizeof(char) * tlenght);
	if (n_str == NULL)
		return (free((char *)s1), NULL);
	while (s1 && s1[i])
	{
		n_str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		n_str[i + j] = s2[j];
		j++;
	}
	n_str[i + j] = '\0';
	return (free((char *)s1), n_str);
}

char	*replace_env_variables(t_msh *msh, char *input_str)
{
	char	*pre_env_part;
	char	*env_var_name;
	char	*final_str;
	char	*env_var_value;

	if (!input_str)
		return (NULL);
	final_str = ft_strdup("");
	while (*input_str)
	{
		pre_env_part = msh_strdup_utill_env(input_str);
		input_str = msh_locate_env_marker(input_str);
		if (!input_str)
		{
			final_str = ft_strjoin_free(final_str, pre_env_part);
			break ;
		}
		env_var_name = ft_strdup_while_string(++input_str, LETTERS_DIGITS);
		env_var_value = fetch_env_variable(msh, env_var_name);
		pre_env_part = ft_strjoin_free(pre_env_part, env_var_value);
		input_str += ft_strlen(env_var_name);
		final_str = ft_strjoin_free(final_str, pre_env_part);
		msh_free_str(pre_env_part, env_var_name, env_var_value);
	}
	return (final_str);
}

void	msh_update_exit_status(t_msh *msh, t_token *current)
{
	free(current->cmd);
	current->cmd = ft_itoa(msh->code);
}

void	msh_strcpy_exit_status(const char *src_str, char *dest_str,
		const char *status_str)
{
	int i, j;
	i = 0;
	while (src_str[i] != '$')
	{
		dest_str[i] = src_str[i];
		i++;
	}
	j = 0;
	while (status_str[j] != '\0')
	{
		dest_str[i + j] = status_str[j];
		j++;
	}
	while (src_str[i + 2] != '\0')
	{
		dest_str[i + j] = src_str[i + 2];
		i++;
	}
	dest_str[i + j] = '\0';
}

void	replace_exit_code(t_msh *msh, t_token *current)
{
	char	*original_cmd;
	char	*status_pos;
	char	*updated_cmd;
	char	*status_str;

	original_cmd = current->cmd;
	if (!original_cmd)
		return ;
	status_pos = ft_strnstr(original_cmd, "$?", ft_strlen(original_cmd));
	if (!status_pos)
		return ;
	status_str = ft_itoa(msh->code);
	updated_cmd = (char *)malloc(sizeof(char) * (ft_strlen(original_cmd) - 1
				+ ft_strlen(status_str)));
	if (!updated_cmd)
		return ;
	msh_strcpy_exit_status(original_cmd, updated_cmd, status_str);
	free(current->cmd);
	free(status_str);
	current->cmd = updated_cmd;
}

void	process_expand(t_msh *msh)
{
	t_token	*token;
	char	*original_command;

	token = msh->token;
	original_command = NULL;
	while (token)
	{
		if (token->type == ENV_VAR)
		{
			if (token->prev && token->prev->type == HEREDOC)
			{
				original_command = token->cmd;
				token->cmd = replace_env_variables(msh, original_command);
				free(original_command);
			}
			else if (token->cmd[0] == '$' && token->cmd[1] == '?')
				msh_update_exit_status(msh, token);
			else if (token->cmd[0] == '$' && token->cmd[1] == '$')
			{
				replace_exit_code(msh, token);
				original_command = token->cmd;
				token->cmd = replace_env_variables(msh, original_command);
				free(original_command);
			}
			else if (!ft_strcmp(token->cmd, "$?"))
				msh_update_exit_status(msh, token);
			else if (ft_strcmp(token->cmd, "$$"))
			{
				replace_exit_code(msh, token);
				original_command = token->cmd;
				token->cmd = replace_env_variables(msh, original_command);
				free(original_command);
			}
		}
		token = token->next;
	}
}

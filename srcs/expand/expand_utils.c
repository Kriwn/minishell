/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:03:55 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/09 09:01:18 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_msh *msh, char *env_name)
{
	int	i;
	int	name_length;

	i = 0;
	name_length = ft_strlen(env_name);
	while (msh->env[i])
	{
		if (ft_strncmp(msh->env[i], env_name, name_length) == 0)
		{
			if (msh->env[i][name_length] == '=')
				return (ft_strdup(ft_strchr(msh->env[i], '=') + 1));
		}
		i++;
	}
	return (NULL);
}

char *fetch_env_variable(t_msh *msh, char *env_name)
{
	char	*env_value;

	if (*env_name == '$')
		return ("$$");
	env_value = get_env_value(msh, env_name);
	if (!env_value)
		env_value = ft_strdup("");
	return (env_value);
}

char	*msh_locate_env_marker(char *str)
{
	while (*str)
	{
		if (*str == '$' && *(str + 1) && !ft_strchr(WHITESPACE, *(str + 1)))
			return (str);
		str++;
	}
	return (NULL);
}

char	*msh_strdup_utill_env(char *str)
{
	int		i;
	int		length;
	char	*dup;
	char	*env_marker;

	if (!str)
		return (NULL);
	env_marker = msh_locate_env_marker(str);
	if (env_marker == NULL)
		return (str);
	length = env_marker - str;
	if (length < 1)
		return (NULL);
	dup = malloc(sizeof(char) * (length + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < length)
	{
		((unsigned char *)dup)[i] = ((unsigned char *)str)[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	msh_free_str(char *str1, char *str2, char *str3)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
}

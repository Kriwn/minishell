/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:07:15 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/27 16:43:12 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env_variable(t_tuple *env, const char *key, const char *value)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

char	*get_env_variable(t_tuple *env, const char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

// cd and cd ~ return to HOME //
int	msh_cd(t_msh *msh, t_token *token)
{
	return (EXIT_SUCCESS);
}

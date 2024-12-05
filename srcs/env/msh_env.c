/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:42:26 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/05 16:07:37 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sort_env(t_tuple **env)
{
	t_tuple	*current;
	t_tuple	*next;
	char	*temp;

	current = *env;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcmp(current->key, next->key) > 0)
			{
				temp = current->key;
				current->key = next->key;
				next->key = temp;
				temp = current->value;
				current->value = next->value;
				next->value = temp;
			}
			next = next->next;
		}
		current = current->next;
	}
}

int	msh_env(t_msh *msh)
{
	t_tuple	*env;

	env = msh->tuple;
	sort_env(&env);
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

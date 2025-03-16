/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:26:50 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/16 02:04:55 by krwongwa         ###   ########.fr       */
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

void	export_no_args(t_p *list)
{
	t_tuple	*current;
	int		saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	current = list->msh->tuple;
	sort_env(&current);
	handle_fd(list);
	print_tuple(current);
	if (list->fd_out != 1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	msh_export(t_p *list)
{
	t_tuple	*new_node;
	t_tuple	**data;
	char	**temp;

	if (list->args[1] == NULL)
	{
		export_no_args(list);
		return (EXIT_SUCCESS);
	}
	data = &list->msh->tuple;
	temp = myft_split(list->args[1], '=');
	if (!temp[0] || !temp[1])
	{
		free2d(temp);
		return (EXIT_FAILURE);
	}
	free2d(temp);
	new_node = malloc(sizeof(t_tuple));
	if (new_node == NULL || make_tuple(new_node, list->args[1], '=') == NULL)
		return (EXIT_FAILURE);
	new_node->next = NULL;
	if (!*data)
	{
		*data = new_node;
		(*data)->tail = new_node;
	}
	else
	{
		(*data)->tail->next = new_node;
		(*data)->tail = new_node;
	}
	return (EXIT_SUCCESS);
}

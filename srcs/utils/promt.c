/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:17:02 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/18 00:57:05 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_promt(t_msh *data)
// {
// 	char	*ans;
// 	char	*temp;
// 	char	*getpath;

// 	getpath = copy(get_value_from_key(data->tuple,"PWD"));
// 	if(!getpath)
// 		getpath = ft_getcwd();
// 	ans = ft_strdup("minishell:");
// 	temp = ft_strjoin(ans, getpath);
// 	ans = temp;
// 	temp = ft_strjoin(ans, " ");
// 	ans = temp;
// 	temp = ft_itoa(data->code);
// 	ans = ft_strjoin(ans, temp);
// 	free(temp);
// 	temp = ft_strjoin(ans, "$ ");
// 	ans = temp;
// 	free(getpath);
// 	return (ans);
// }

void	free_heredoc_nodes(t_ast *node)
{
	if (!node)
		return ;
	free_heredoc_nodes(node->left);
	free_heredoc_nodes(node->right);
	if (node->args)
	{
		if (node->args[0])
			free(node->args[0]);
		free(node->args);
	}
	free(node);
}

void	ft_error(t_msh *data, char *word)
{
	ft_putstr_fd(word, 2);
	ft_free(data);
	exit(EXIT_FAILURE);
}

char	*get_promt(void)
{
	return (ft_strdup("minishell: "));
}

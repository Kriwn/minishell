/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:17:02 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/17 17:14:10 by jikarunw         ###   ########.fr       */
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

char	*get_promt(t_msh *data)
{
	return (ft_strdup("minishell: "));
}

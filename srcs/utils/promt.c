/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:17:02 by krwongwa          #+#    #+#             */
/*   Updated: 2024/07/26 20:05:20 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_promt(t_env *data)
{
	char	*ans;
	char	*temp;

	// ans = ft_pwd(data->tuple);
	ans = ft_strdup("minishell:");
	temp = ft_strjoin(ans, " ");
	ans = temp;
	temp = ft_itoa(data->code);
	ans = ft_strjoin(ans, temp);
	free(temp);
	temp = ft_strjoin(ans, "$ ");
	ans = temp;
	return (ans);
}

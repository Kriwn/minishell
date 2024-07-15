/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:17:02 by krwongwa          #+#    #+#             */
/*   Updated: 2024/07/15 16:19:35 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_promt(t_env *data)
{
	char	*ans;
	char	*temp;

	ans = ft_pwd(data->tuple);
	temp = ft_strjoin(ans, " ");
	ans = temp;
	temp = ft_itoa(data->code);
	ans = ft_strjoin(ans, temp);
	free(temp);
	temp = ft_strjoin(ans, "$ ");
	ans = temp;
	return (ans);
}

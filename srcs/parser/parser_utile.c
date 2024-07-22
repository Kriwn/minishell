/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:00 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/21 23:53:13 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	**ft_split_pipe(char *str)
{
	char	**ans;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	ans = (char **)malloc(sizeof(char *) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '|')
		{
			ans[j] = (char *)malloc(sizeof(char) * (i - k + 1));
			ft_strlcpy(ans[j], str + k, i - k + 1);
			ans[j][i - k] = '\0';
			k = i + 1;
			j++;
		}
		i++;
	}
	ans[j] = (char *)malloc(sizeof(char) * (i - k + 1));
	ft_strlcpy(ans[j], str + k, i - k + 1);
	ans[j][i - k] = '\0';
	j++;
	ans[j] = NULL;
	return (ans);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:00 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/26 16:55:06 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	trim_first_space(char *input, t_token *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] == ' ')
		i++;
	token->input_cmd = malloc(ft_strlen(input) - i + 1);
	while (input[i])
		token->input_cmd[j++] = input[i++];
	token->input_cmd[j] = '\0';
}

char	**msh_split_pipe(char *str)
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

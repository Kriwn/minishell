/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/22 22:59:46 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_first_space(char *input, t_token *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] == ' ')
		i++;
	token->input_cmd = malloc(strlen(input) - i + 1);
	while (input[i])
		token->input_cmd[j++] = input[i++];
	token->input_cmd[j] = '\0';
}

int	check_pipe(char *input)
{
	t_token	token;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(input, '|');
	while (tmp[i])
	{
		trim_first_space(tmp[i], &token);
		printf("[%d]: %s\n", i, token.input_cmd);
		free(token.input_cmd);
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (0);
}

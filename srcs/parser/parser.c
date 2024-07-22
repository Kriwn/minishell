/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/22 13:02:17 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*trim_first_space(char *input)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		input[j] = input[i];
		i++;
		j++;
	}
	input[j] = '\0';
}

int check_pipe(char *input)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(input, '|');
	while (tmp[i])
	{
		trim_first_space(tmp[i]);
		printf("[%d]: %s\n", i, tmp[i]);
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return 0;
}

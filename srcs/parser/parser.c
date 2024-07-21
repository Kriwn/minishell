/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/21 23:54:42 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_pipe(char *input)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(input, '|');
	while (tmp[i]) {
		printf("[%d]: %s\n", i, tmp[i]);
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return 0;
}

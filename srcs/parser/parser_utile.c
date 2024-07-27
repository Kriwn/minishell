/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:00 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/26 19:30:43 by jikarunw         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:00 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/28 00:07:00 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_error(char *err)
{
	t_env *env;

	env->code = 2;
	printf("syntax error near unexpected token `%s'\n", err);
}

void free_split_result(char **result)
{
	char **temp = result;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(result);
}

void free_token(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return;
	if (token->tokens)
	{
		while (token->tokens[i++])
			free(token->tokens[i]);
		free(token->tokens);
	}
	free(token);
}

void trim_first_space(char *input, t_token *token)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (input[i] == ' ')
		i++;
	token->input_cmd = malloc(ft_strlen(input) - i + 1);
	while (input[i])
		token->input_cmd[j++] = input[i++];
	token->input_cmd[j] = '\0';
}

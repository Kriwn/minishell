/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:01:05 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/27 17:46:26 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_pipe(char *input)
{
	t_token	token;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(input, '|');
	while (tmp[i])
	{
		trim_first_space(tmp[i], &token);
		// printf("[%d]: %s\n", i, token.input_cmd);
		free(token.input_cmd);
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (token.input_cmd);
}

char	*msh_input_cmd(char *input)
{
	t_token	token;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(input, '|');
	while (tmp[i])
	{
		trim_first_space(tmp[i], &token);
		free(token.input_cmd);
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (token.input_cmd);
}

int	msh_parsing(char *input)
{
	t_token	token;
	char	**tmp;
	int		i;

	if (!input)
		return (-1);
	token.input_cmd = msh_input_cmd(input);

	while (token.cmd[i] != NULL)
	{
		if (ft_strcmp(token.input_cmd, token.cmd[i]) != 0)
			printf("%s: command not found\n", token.cmd[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:03:29 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/24 23:03:33 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_status_with_value(t_msh *shell, t_token *current)
{
	free(current->cmd);
	current->cmd = ft_itoa(shell->code);
}

void	replace_exit_status(char *original, char *replacement, char *exit_code)
{
	int	i;
	int	j;

	i = 0, j = 0;
	while (original[i] != '$')
	{
		replacement[i] = original[i];
		i++;
	}
	while (exit_code[j])
	{
		replacement[i + j] = exit_code[j];
		j++;
	}
	while (original[i + 2])
	{
		replacement[i + j] = original[i + 2];
		i++;
	}
	replacement[i + j] = '\0';
}

void	expand_exit_code(t_msh *shell, t_token *current)
{
	char	*original;
	char	*exit_code;
	char	*replacement;

	original = current->cmd;
	if (!original)
		return ;
	if (!ft_strnstr(original, "$?", ft_strlen(original)))
		return ;
	exit_code = ft_itoa(shell->code);
	replacement = malloc(ft_strlen(original) - 1 + ft_strlen(exit_code));
	if (!replacement)
		return ;
	replace_exit_status(original, replacement, exit_code);
	free(current->cmd);
	free(exit_code);
	current->cmd = replacement;
}

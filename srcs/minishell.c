/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:25:02 by krwongwa          #+#    #+#             */
/*   Updated: 2024/07/26 17:33:26 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(t_env *var)
{
	char	*input;
	char	*promt;

	promt = get_promt(var);
	input = readline(promt);
	if (promt)
		free(promt);
	add_history(input);
	return (input);
}

int	main(int ac,char **av,char **env)
{
	t_env	var;
	t_token	token;
	char	*input;

	init_minishell(&var, env);
	while (1)
	{
		input = ft_readline(&var);
		msh_parsing(input);
		if (input)
			free(input);
		if (input == NULL)
			break ;
	}
	ft_free(&var);
	print_tuple(var.tuple);
	rl_clear_history();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:25:02 by krwongwa          #+#    #+#             */
/*   Updated: 2024/07/06 19:14:00 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"

char *ft_readline()
{
	char	*input;
	char	*promt;

	promt = getcwd(NULL, 0);
	input = readline(promt);
	// add_history(input);
	return (input);
}

// -lreadline
int main(int ac,char **av,char **env)
{
	t_env	var;
	char	*input;

	var.tuple = NULL;
	// init_minishell()
	init_tuple(&var.tuple, env);
	print_tuple(var.tuple);
	// while (1)
	// {
	// 	input = ft_readline();
	// }
    return (0);
}

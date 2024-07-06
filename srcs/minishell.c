/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:25:02 by krwongwa          #+#    #+#             */
/*   Updated: 2024/07/06 22:52:55 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_readline()
{
	char	*input;
	char	*promt;

	promt = getcwd(NULL, 0);
	input = readline(promt);
	// add_history(input);
	return (input);
}

// -lreadline
// int	main(int ac,char **av,char **env)
// {
// 	t_env	var;
// 	char	*input;

// 	var.tuple = NULL;
// 	// init_minishell()
// 	init_tuple(&var.tuple, env);
// 	print_tuple(var.tuple);
// 	// while (1)
// 	// {
// 	// 	input = ft_readline();
// 	// }
// 	return (0);
// }

int	main(void)
{
	
	return (0);
}

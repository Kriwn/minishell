/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:25:02 by krwongwa          #+#    #+#             */
/*   Updated: 2024/07/27 17:48:59 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t g_signal;

void	check_signal(int signal)
{

	if (signal ==  SIGINT && g_signal == 0)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (signal == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
}

int	setup_signal()
{
	struct sigaction act;

	g_signal = 0;
	ft_bzero(&act, sizeof(sigaction));
	act.sa_handler =  &check_signal;
	act.sa_flags = SA_RESTART;

	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);

	ft_bzero(&act, sizeof(sigaction));
}

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

int	main(int ac, char **av, char **env)
{
	t_env	var;
	t_token	token;
	char	*input;

	init_minishell(&var, env);
	setup_signal();
	while (1)
	{
		input = ft_readline(&var);
		msh_parsing(input);
		if (input)
			free(input);
		if (input == NULL)
			break ;
		check_pipe(input);
		if (input)
			free(input);
	}
	ft_free(&var);
	print_tuple(var.tuple);
	rl_clear_history();
	return (0);
}

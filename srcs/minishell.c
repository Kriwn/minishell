/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:25:02 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/27 19:22:06 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal;

void	check_signal(int signal)
{
	if (signal == SIGINT && g_signal == 0)
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

int	setup_termios(void)
{
	struct termios	config;

	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("Not a terminal.\n", 2);
		return (-1);
	}
	tcgetattr(STDIN_FILENO, &config);
	config.c_lflag &= ~(ECHOCTL | ICANON);
	config.c_cc[VMIN] = 0;
	config.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &config);
	return (1);
}

void	setup_signal(void)
{
	struct sigaction	act;

	g_signal = 0;
	ft_bzero(&act, sizeof(sigaction));
	act.sa_handler = &check_signal;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	ft_bzero(&act, sizeof(sigaction));
}

char	*ft_readline(t_msh *var)
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
	t_msh	*msh;
	t_token	*token;
	t_ast	*ast;
	char	*input;
	int		status;

	msh = malloc(sizeof(t_msh));
	if (!msh)
		return (1);
	init_minishell(msh, env);
	setup_signal();
	if (setup_termios() == -1)
	{
		ft_error(msh, "Termios setup error\n");
		ft_free(msh);
		return (1);
	}
	while (1)
	{
		input = ft_readline(msh);
		if (!input)
		{
			printf("%sEXIT!%s💥\n", RED, RESET);
			break ;
		}
		token = msh_parsing_input(input);
		if (token)
			ast = msh_get_tokens(&token);
		if (ast)
		{
			// display_ast(ast, 0);
			display_ast_table(ast, 0);
			status = execute_ast(ast, msh);
		}
	}
	free(ast->args);
	free(ast->args[0]);
	ft_free(msh);
	print_tuple(msh->tuple);
	rl_clear_history();
	return (0);
}

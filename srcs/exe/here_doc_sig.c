/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_sig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:30:45 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/21 21:41:57 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal;

int	clear_read_line(void)
{
	if (g_signal == 1)
	{
		rl_on_new_line();
		rl_replace_line("\n", 1);
		rl_redisplay();
		rl_done = 1;
	}
	return (0);
}

void	here_doc_check_signal(int sig)
{
	if (sig == SIGINT)
		g_signal = 1;
}

void	end_here_doc(t_p *list)
{
	dprintf(2,"End Here\n");
	if (g_signal == 1)
		*list->code = 130;
	g_signal = 0;
	signal(SIGINT, &check_signal);
	rl_event_hook = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:01 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/18 12:49:10 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal;


static int	clear_read_line(void)
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

void	do_here_doc_task(t_ast *ast,t_p *list)
{
	if (!ast)
		return ;
	if (ast->type == HEREDOC)
		list->fd_in = do_here_doc(ast->right,ast->left ,list);
	else
	{
		do_here_doc_task(ast->left, list);
		do_here_doc_task(ast->right, list);
	}
}

int init_here_doc(t_ast *ast,t_ast *temp, t_p *list)
{
	if (pipe(list->pipe)== -1)
	{
		ft_puterrstr("PIPE ERROR");
		return (-1);
	}
	if (temp != NULL)
	{
		if (temp->type == REDIRECT)
			list->fd_out = open(temp->right->args[0],O_RDWR | O_TRUNC | O_CREAT, 0644);
		else if (temp->type == APPEND)
			list->fd_out = open(temp->right->args[0],O_RDWR | O_APPEND | O_TRUNC | O_CREAT, 0644);
	}
	g_signal = 0;
	signal(SIGINT, &here_doc_check_signal);
	rl_event_hook = &clear_read_line;
	return (0);
}

// cannot do "" here_doc
int	do_here_doc(t_ast *ast,t_ast *temp ,t_p *list)
{
	char	*getline;
	char	*str;
	int		fd[2];

	str = ast->args[0];
	dprintf(2,"Temp\n");
	if (init_here_doc(ast,temp,list) == -1)
		return (-1);
	if (list->fd_out != -1)
	{
		dup2(list->fd_out, list->pipe[1]);
		safe_close(list,1);
	}
	dprintf(2,"Before start here\n");
	while (1)
	{
		getline = readline("> ");
		if (getline == NULL  || g_signal == 1 || ft_strncmp(getline, str, ft_strlen(str)) == 0 )//need to add signal here
			break ;
		write(list->pipe[1], getline, ft_strlen(getline));
		write(list->pipe[1], "\n", 1);
		free(getline);
	}
	end_here_doc(list);
	if (getline)
		free(getline);
	close(list->pipe[1]);
	return (list->pipe[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:01 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/20 23:20:45 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	do_here_doc_task(t_token *cur,t_p *list)
{
	while (cur)
	{
		if (cur->type == HEREDOC)
		{
			list->fd_in = do_here_doc(cur->next->cmd, list);
		}
		cur = cur->next;
	}
}

int	do_here_doc(char *str, t_p *list)
{
	char	*getline;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_puterror("Pipe error", errno, list);
	// set mode for here file
	while (1)
	{
		getline = readline("> ");
		if (getline == NULL || g_signal == 1 || ft_strncmp(getline, str, ft_strlen(str)) == 0)
			break ;
		write(fd[1], getline, ft_strlen(getline));
		write(fd[1], "\n", 1);
		free(getline);
	}
	// set to normal mode
	if (getline)
		free(getline);
	close(fd[1]);
	return (fd[0]);
}

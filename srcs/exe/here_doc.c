/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:01 by krwongwa          #+#    #+#             */
/*   Updated: 2024/12/13 13:37:56 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern volatile sig_atomic_t	g_signal;

void	do_here_doc_task(t_ast *ast,t_p *list)
{
	if (!ast)
		return ;
	if (ast->type == HEREDOC)
		do_here_doc(ast->right,ast->left ,list);
	else
	{
		do_here_doc_task(ast->left, list);
		do_here_doc_task(ast->right, list);
	}
}

// need to do open infile and out file for all using pipe
// try << test < a >> d it should not have someting in d
// if SIG INT exit code 130
int	do_here_doc(t_ast *ast,t_ast *temp ,t_p *list)
{
	char	*getline;
	char	*str;
	int		fd[2];
	str = ast->args[0];
	printf("%s\n",str); //str
	printf("%s\n",temp->right->args[0]); //out
	if (pipe(fd) == -1)
		printf("Error pipe\n");
	if (temp->type == REDIRECT)
		fd[1] = open(temp->right->args[0],O_RDWR | O_TRUNC | O_CREAT, 0644);
	else if (temp->type == APPEND)
		fd[1] = open(temp->right->args[0],O_RDWR | O_APPEND | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		getline = readline("> ");
		if (getline == NULL || ft_strncmp(getline, str, ft_strlen(str)) == 0)//need to add signal here
			break ;
		write(fd[1], getline, ft_strlen(getline));
		write(fd[1], "\n", 1);
		free(getline);
	}
	if (getline)
		free(getline);
	close(fd[1]);
	list->fd_in = fd[0];
	return (fd[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:01 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/28 14:50:14 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	do_here_doc_task(t_ast *ast,t_p *list)
{
	if (!ast)
		return ;
	if (ast->type == HEREDOC)
		do_here_doc(ast->right, list);
	else
	{
		do_here_doc_task(ast->left, list);
		do_here_doc_task(ast->right, list);
	}
}


int	do_here_doc(t_ast *ast, t_p *list)
{
	char	*getline;
	char	*str;
	int		fd[2];

	printf("DO HERE DOC\n");
	str = ast->args[0];
	printf("%s\n", str);
	printf("After\n");
	printf("%d\n",ast->right->left->type);

	// if (pipe(fd) == -1)
	// 	ft_puterror("Pipe error", errno, list);
	// while (1)
	// {
	// 	getline = readline("> ");
	// 	if (getline == NULL || g_signal == 1 || ft_strncmp(getline, str, ft_strlen(str)) == 0)
	// 		break ;
	// 	write(fd[1], getline, ft_strlen(getline));
	// 	write(fd[1], "\n", 1);
	// 	free(getline);
	// }
	// // set to normal mode
	// if (getline)
	// 	free(getline);
	// close(fd[1]);
	// return (fd[0]);
}

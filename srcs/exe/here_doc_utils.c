/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:08:42 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/12 19:40:02 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_here_doc_task(t_ast *ast, t_p *list, int *b)
{
	int	status;

	status = 0;
	if (!ast)
		return ;
	if (ast->type == HEREDOC)
		list->fd_in = do_here_doc(ast->right, ast->left, list);
	if (ast->type == CMD)
		*b = 1;
	else
	{
		do_here_doc_task(ast->left, list, b);
		do_here_doc_task(ast->right, list, b);
	}
}

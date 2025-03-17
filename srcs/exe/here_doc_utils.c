/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:08:42 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/18 00:58:01 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_here_doc_task(t_ast *ast, t_p *list, int *isBuildIn)
{
	if (!ast)
		return ;
	if (ast->type == HEREDOC)
		list->fd_in = do_here_doc(ast->right, ast->left, list);
	if (ast->type == CMD)
		*isBuildIn = 1;
	else
	{
		do_here_doc_task(ast->left, list, isBuildIn);
		do_here_doc_task(ast->right, list, isBuildIn);
	}
}

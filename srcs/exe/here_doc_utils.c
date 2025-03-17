/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:08:42 by krwongwa          #+#    #+#             */
/*   Updated: 2025/03/17 20:20:38 by krwongwa         ###   ########.fr       */
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

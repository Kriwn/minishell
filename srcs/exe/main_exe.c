/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:03 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/20 23:19:18 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main_exe(t_msh *msh){

	t_token *curr;
	t_p		*list;

	curr = msh->token;
	list = msh->list;
	list->env = msh->env;
	list->path = ft_split(get_value_from_key(msh->tuple, "PATH="), ':');
	do_here_doc_task(&curr,list);
	//clear_here_doc form list
	while(curr)
	{
		if (pipe(list->pipe) == -1)
			ft_puterror("Pipe error", errno, list);
		list->process_pid

		curr = curr->next;
	}
}

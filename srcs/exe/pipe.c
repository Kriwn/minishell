/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:28:33 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/21 15:28:53 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_task(	t_token *curr,t_p	*list){

	t_token *curr;
	int		count;
	t_p		*list;

	count = 0;
	while(curr)
	{
		if (pipe(list->pipe) == -1)
			ft_puterror("Pipe error", errno, list);
		list->process_pid[count] = fork();
		//check is it build in command or not
		curr = curr->next;
	}
}

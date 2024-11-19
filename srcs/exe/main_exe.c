/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:03 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/18 18:31:46 by krwongwa         ###   ########.fr       */
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
	//checkhere_doc
	while(curr)
	{


		curr = curr->next;
	}
}

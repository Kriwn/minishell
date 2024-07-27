/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:38:01 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/28 01:02:29 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRCUT_H
# define STRCUT_H

#include "./minishell.h"

/***************
 * PARSER TYPE *
 ***************/
typedef struct s_token
{
	char	*input_cmd;
	char	**cmd;
	char	**tokens;
	int		count;
}	t_token;

/******************
 * EXECUTION TYPE *
 ******************/
typedef struct tuple
{
	char		*key;
	char		*value;
	struct	tuple *next;
	struct	tuple *tail;
} t_tuple;

typedef struct p_pipe
{
	int		*process_pid;
	int		status_pid;
	char	**env;
	char	**path;
	char	*cmd;
	int		fd_in;
	int		fd_out;
}	t_p;

typedef struct	e_env
{
	t_tuple	*tuple;
	char	**env;
	char	*home_path;
	int		code;
}	t_env;

/*****************
 * PROGRAM TRAIN *
 *****************/

// typedef struct	s_msh
// {
// 	// Wait for use nextime;
// }	t_msh;

#endif

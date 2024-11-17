/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:38:01 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/17 15:24:24 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRCUT_H
# define STRCUT_H

#include "./minishell.h"

typedef enum s_type
{
	CMD, // command, built-in
	EMPTY,	// ""
	INDIRECT, // <
	REDIRECT, // >
	PIPE, // |
	APPEND, // >>
	HEREDOC, // <<
	ARG, // argument
	END // ;
}	t_type;

/***************
 * PARSER TYPE *
 ***************/
typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
	int				count;
	char			**tokens;
	char			*cmd;
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

/*****************
 * PROGRAM TRAIN *
 *****************/

typedef struct	s_msh
{
	t_tuple	*tuple;
	t_token *token;

	char	*home_path;
	int		code; // -> status code
	char	**env;
	char	*cwd;
}	t_msh;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:38:01 by jikarunw          #+#    #+#             */
/*   Updated: 2024/09/07 01:48:56 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRCUT_H
# define STRCUT_H

#include "./minishell.h"

# define EMPTY 0
# define CMD 1
# define INDIRECT 2 
# define REDIRECT 3
# define PIPE 4
# define APPEND 5
# define HEREDOC 6
# define ARG 7
# define END 8

/***************
 * PARSER TYPE *
 ***************/
typedef struct s_token
{
	char			*str;
	int				type;
	int				quote_end;
	int				quote_type;
	int				quote_space;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	struct s_env	*next;
	char			var_cpy[1024];
	char			*expanded_value;
	char			*value;
}	t_env;

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
	int		code;
}	t_msh;

#endif

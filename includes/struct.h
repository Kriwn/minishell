/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:38:01 by jikarunw          #+#    #+#             */
/*   Updated: 2024/12/24 01:31:07 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRCUT_H
# define STRCUT_H

#include "./minishell.h"

typedef enum s_type
{
	CMD, // command, built-in
	ARG, // argument
	ENV_VAR, // -> "$HOME"
	EMPTY,	// ""
	INDIRECT, // <
	REDIRECT, // >
	PIPE, // |
	APPEND, // >>
	HEREDOC, // <<
	HEREDOC_WORD, // <<-
	END, // ; -> maybe this's not use for now.
	/** Maybe this two type to use the lexer
	 * &&
	 * ||
	 */
	CMD_GROUP, // -> (command child)
}	t_type;

/*****************
 * PROGRAM TRAIN *
 *****************/

typedef struct	s_msh
{
	struct tuple	*tuple;
	struct s_token	*token;
	struct s_ast	*ast;
	struct p_pipe	*list;
	char			*home_path;
	int				code;
	char			**env;
	char			*cwd;
	int				count_pipe;
	char			*input;
}	t_msh;

/***************
 * PARSER TYPE *
 ***************/
typedef struct s_token
{
	char			*cmd;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_ast
{
	t_type			type;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_expan
{
	char			*new_arg;
	int				i;
	int				j;
}				t_expan;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
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
	int		pipe[2];
	int		*process_pid;
	char	**path;
	char	*cmd;
	char	**env;
	char	**args;
	int		max;
	int		fd_in;
	int		fd_out;
	int		iter;
	int		*code;
	char	*here_doc_cut;
}	t_p;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:38:01 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/12 19:59:05 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./minishell.h"

typedef enum s_type
{
	CMD,
	ARG,
	ENV_VAR,
	EMPTY,
	INDIRECT,
	REDIRECT,
	PIPE,
	APPEND,
	HEREDOC,
	HEREDOC_WORD,
	END,
	CMD_GROUP,
}	t_type;

/*****************
 * PROGRAM TRAIN *
 *****************/

typedef struct s_msh
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
	t_msh			*msh;
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

/******************
 * EXECUTION TYPE *
 ******************/
typedef struct tuple
{
	char			*key;
	char			*value;
	struct tuple	*next;
	struct tuple	*tail;
}	t_tuple;

typedef struct p_pipe
{
	int				pipe[2];
	int				*process_pid;
	char			**path;
	char			*cmd;
	char			**env;
	char			**args;
	t_msh			*msh;
	int				fd_in;
	int				fd_out;
	int				iter;
	int				*code;
	char			*here_doc_cut;
}	t_p;

#endif

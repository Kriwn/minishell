/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:29:56 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/20 23:26:44 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include "../libft/includes/libft.h"
# include <stdbool.h>

# include "../libft/includes/libft.h"
# include "./struct.h"
# include <termios.h>

/*************************
 * SRCS/BUILDIN/FT_PWD.C *
 *************************/
char		*ft_pwd(t_tuple *list);
int			(*init_builtin(char *str))(t_msh *msh);

int			msh_echo(t_msh *msh, t_token *token);
int			msh_pwd(t_msh *msh);
int			msh_cd(t_msh *msh, t_token *token);

int			get_env(t_msh *msh);

/***************************
 * SRCS/UTILS/TUPLE_LIST.C *
 ***************************/
void		print_tuple(t_tuple *data);
char		*get_value_from_key(t_tuple *data,char *key);
void		updata_value_from_key(t_tuple *data, char *key, char *new_value);
void		remove_tuple(t_tuple **data, char *key);
void		clear_tuple(t_tuple **data);

/**********************
 * SRCS/UTILS/UTILS.C *
 **********************/
void		ft_free(t_msh *data);
void		ft_error(t_msh *data,char *word);

/**********************
 * SRCS/UTILS/PROMT.C *
 **********************/
char		*get_promt(t_msh *data);

/******************************
 * SRCS/INIT/INIT_MINISHELL.C *
 ******************************/
void		init_minishell(t_msh *data, char **env);

/**************************
 * SRCS/INIT/INIT_TUPLE.C *
 **************************/
int			init_tuple(t_tuple **data,char **env);
void		*make_tuple(t_tuple *new_node,char *str,char c);

/************************
 * SRCS/PARSER/PARSER.C *
 ************************/
t_token		*msh_input(char *input);
int			msh_execute_commands(t_token *tokens);
t_token		*msh_parse_tokens(char *input);
int			msh_parsing(char *input);

/****************************
 * SRCS/PARSER/PARSER_UTILS *
 ****************************/
/** Old Function Do's It */
const char	*msh_name_type(t_type type);
/** New Function*/
t_ast		*msh_init_ast(t_type type);
void		msh_free_ast(t_ast *node);
t_ast		*create_file_list_redir(t_token **tokens, t_token *tmp);
int			count_cmd_arg(t_token *current);
void		add_cmd_arg(t_ast *cmd_node, t_token **tokens, int arg_count);

t_ast		*file_ast_node(t_token *token);
t_ast		*msh_get_cmd(t_token **tokens);
t_ast		*msh_get_redirect(t_token **tokens);
t_ast		*msh_get_pipe(t_token **tokens);
t_ast		*msh_get_tokens(t_token **tokens);



/***************
 * SRCS/TOKEN/ *
 ***************/
/** It try to do lexer node
 */
t_token		*new_token(t_type type, char *value);
void		parse_cmd(char **input, t_token **tokens);
void		parse_cmd(char **input, t_token **tokens);
void		parse_type(char **input, t_token **tokens);
t_type		get_token_type(const char **input);

t_token		*token_input(char *input);
t_token		*msh_parsing_input(char *input);
void		display_tokens(t_token *tokens);
void		test_delete_heredoc(t_token **tokens);
void		delete_token_heredoc(t_token **tokens);
#endif

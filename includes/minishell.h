/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:29:56 by jikarunw          #+#    #+#             */
/*   Updated: 2024/11/17 15:36:04 by jikarunw         ###   ########.fr       */
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
void		free_msh_context(t_msh *msh);
void		free_split_result(char **result);
void		free_token(t_token *token);

t_token		*msh_init_token(char *token_str, t_token *prev);
void		msh_check_cmd(t_token *token);
t_msh		*init_msh_context(char **envp);
t_type		msh_get_type(const char *token_str);
const char	*msh_name_type(t_type type);

/*************************
 * SRCS/PARSER/MSH_SPLIT *
 *************************/
t_token		*msh_split(char *str, const char *symbol);

#endif

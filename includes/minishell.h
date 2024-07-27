/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:29:56 by jikarunw          #+#    #+#             */
/*   Updated: 2024/07/28 01:46:30 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

/*************************
 * SRCS/BUILDIN/FT_PWD.C *
 *************************/
char	*ft_pwd(t_tuple *list);

/***************************
 * SRCS/UTILS/TUPLE_LIST.C *
 ***************************/
void	print_tuple(t_tuple *data);
char	*get_value_from_key(t_tuple *data,char *key);
void	updata_value_from_key(t_tuple *data, char *key, char *new_value);
void	remove_tuple(t_tuple **data, char *key);
void	clear_tuple(t_tuple **data);

/**********************
 * SRCS/UTILS/UTILS.C *
 **********************/
void	ft_free(t_msh *data);
void	ft_error(t_msh *data,char *word);

/**********************
 * SRCS/UTILS/PROMT.C *
 **********************/
char	*get_promt(t_msh *data);

/******************************
 * SRCS/INIT/INIT_MINISHELL.C *
 ******************************/
void	init_minishell(t_msh *data, char **env);

/**************************
 * SRCS/INIT/INIT_TUPLE.C *
 **************************/
int		init_tuple(t_tuple **data,char **env);
void	*make_tuple(t_tuple *new_node,char *str,char c);

/************************
 * SRCS/PARSER/PARSER.C *
 ************************/
t_token	*msh_input(char *input);
int		msh_parsing(char *input);

/****************************
 * SRCS/PARSER/PARSER_UTILS *
 ****************************/
void	trim_first_space(char *input, t_token *token);
void	free_split_result(char **result);
void	free_token(t_token *token);

/*************************
 * SRCS/PARSER/MSH_SPLIT *
 *************************/
char	**msh_split(char *str, const char *symbol);

#endif

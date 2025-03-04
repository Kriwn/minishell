/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:29:56 by jikarunw          #+#    #+#             */
/*   Updated: 2025/03/05 01:06:47 by jikarunw         ###   ########.fr       */
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
# include <fcntl.h>
# include <signal.h>
# include "../libft/includes/libft.h"
# include <stdbool.h>
# include <errno.h>

#include <sys/wait.h>
#include <fcntl.h>

# include "../libft/includes/libft.h"
# include "./struct.h"
# include <termios.h>

# define STDERR_FILENO 2
# define WHITESPACE " \t\n\v\f\r"
# define LETTERS_DIGITS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

/**************
 * SRCS/UTILS *
 **************/
void		print_tuple(t_tuple *data);
char		*get_value_from_key(t_tuple *data,char *key);
void		updata_value_from_key(t_tuple *data, char *key, char *new_value);
void		remove_tuple(t_tuple **data, char *key);
void		clear_tuple(t_tuple **data);

void		free_ast(t_ast *ast);
void		ft_free(t_msh *data);
void		ft_error(t_msh *data,char *word);

char		*get_promt(t_msh *data);

/*************
 * SRCS/INIT *
 *************/
int			init_tuple(t_tuple **data, char **env);
void		*make_tuple(t_tuple *new_node, char *str, char c);

void		init_minishell(t_msh *data, char **env);

/** init_parsing */
t_ast		*file_ast_node(t_token *token);
t_ast		*msh_init_ast(t_type type);

/****************
 * SRCS/BUILTIN *
 ****************/
int			msh_execute_builtin(t_p *list);
int			msh_exit(t_msh *msh);
int			msh_pwd(t_p *list);
int			msh_echo(t_p *list);
int			msh_cd(t_msh *msh, t_token *token);
int			msh_env(t_p *list);
int			msh_export(t_p *list);
int			msh_unset(t_p *list);

void		update_env_variable(t_tuple *env, const char *key, const char *value);
char		*get_env_variable(t_tuple *env, const char *key);

/***************
 * SRCS/EXPAND *
 ***************/

void	replace_status_with_value(t_msh *shell, t_token *current);
void	replace_exit_status(char *original, char *replacement, char *exit_code);
void	expand_exit_code(t_msh *shell, t_token *current);
char	*fetch_environment_value(t_msh *shell, char *key);
char	*get_variable_value(t_msh *shell, char *key);

char	*locate_variable_reference(char *str);
char	*duplicate_until_variable(char *str);
void	free_multiple_strings(char *s1, char *s2, char *s3);

char	*expand_variables(t_msh *shell, char *original_str);
void	process_expansion(t_msh *shell);
char	*msh_expand_variable(t_msh *shell, char *token_value);

/***************
 * SRCS/PARSER *
 ***************/
/** msh_parsing */
t_ast		*msh_get_tokens(t_token **tokens);

t_ast		*msh_get_pipe(t_token **tokens);
t_ast		*msh_get_redirect(t_token **tokens);
t_ast		*msh_get_heredoc_word(t_token **token);
t_ast		*msh_get_cmd(t_token **tokens);

/** parsing_utils_01 */
void		msh_free_ast(t_ast *node);
t_ast		*create_file_list_redir(t_token **tokens, t_token *tmp);
int			count_cmd_arg(t_token *current);
void		add_cmd_arg(t_ast *cmd_node, t_token **tokens, int arg_count);

/** msh_syntax */
int			has_unclosed_quotes(const char *input);
int			has_invalid_redirections(const char *input);
int			has_misplaced_operators(const char *input);
int			has_logical_operators(const char *input);
int			syntax_error_checker(const char *input);

/** syntax_utils_01 */
void		update_quote_counts(char c, int *s_q_count, int *d_q_count);
int			is_invalid_operator(const char **input);

/**************
 * SRCS/TOKEN *
 **************/
t_token		*msh_parsing_input(t_msh *msh);
t_token		*token_input(char *input);
void		msh_count_pipe(t_msh *msh);

t_token		*new_token(t_type type, char *value);
void		add_token_to_list(t_token **tokens, t_token *new_token);
void		add_word_token_if_valid(char **start, char **input, t_token **tokens);
void		parse_cmd(char **input, t_token **tokens);
void		parse_type(char **input, t_token **tokens);

void		update_quote_status(char c, int *in_quote, char *quote_char);
// void		parse_type(char **input, t_token **tokens, t_msh *msh);

/** File: Test Function for show Display */
const char	*msh_name_type(t_type type);
void		test_delete_heredoc(t_token **tokens);
void		display_ast_table(t_ast *ast, int level);
void		display_tokens(t_token *tokens);
void		display_ast(t_ast *ast, int idx);

/************
 * SRCS/EXE *
 ************/
int			find_slash(char *command);
int			do_here_doc(t_ast *ast,t_ast *temp ,t_p *list);
void		is_build_in_command(t_ast *ast,int *a);
int			check_build_in_command(char *word,int *a);
// int 		check_build_in_command(char *word);
void		do_here_doc_task(t_ast *ast,t_p *list,int *b);
void		main_exe(t_msh *msh);
void		safe_close(t_p *list, int flag);
void		prepare_cmd(t_ast *ast,t_p *list, int *status);
void		open_in_file(char *argv, t_p *list,int *status);
void		open_out_file(char *argv, t_p *list,int flag, int *status);
void		pipe_write(t_p *list);
char 		*find_path(char *cmd, char **path);
void		pipe_task(t_ast *ast, t_p *list);
void		clear_list(t_p *list);
void 		free_list(t_p *list);
void		ft_puterrstr(char *s);
int			ft_puterrorcmd(char *s, int errnum);
void	check_signal(int signal);
void	mode_signal_exe(int mode);
void	wait_all_process(t_p *list);
void		exe_single_cmd(t_ast *ast, t_p *list);
char	**myft_split(char const *s, char c);

#endif

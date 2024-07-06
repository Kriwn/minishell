#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

# include "exe.h"
# include "parser.h"



void	*make_tuple(t_tuple *new_node,char *str,char c);
void	print_tuple(t_tuple *data);

/**************************
 * SRCS/INIT/INIT_TUPLE.C *
 **************************/
void	init_tuple(t_tuple **data,char **env);

#endif

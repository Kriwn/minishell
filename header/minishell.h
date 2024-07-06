#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

#include "struct.h"


size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	*make_tuple(t_tuple *new_node,char *str,char c);
void	init_tuple(t_tuple **data,char **env);
void	print_tuple(t_tuple *data);

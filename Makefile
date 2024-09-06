NAME = minishell
PATH_HEADER = includes
PATH_LIBFT = libft
PATH_SRCS = srcs
OBJ_DIR = objs

CC = cc
# CFLAGS = -Wall -Wextra -Werror -I$(PATH_HEADER) -I$(PATH_LIBFT) -g
CFLAGS = -g -I$(PATH_LIBFT) -I$(PATH_HEADER)
LDFLAGS = -L$(PATH_LIBFT) -lft -lreadline

RM = rm -rf

INIT_DIR = srcs/init/
INIT_FILE = init_tuple.c init_minishell.c
INIT_SRC = $(addprefix $(INIT_DIR), $(INIT_FILE))

UTILS_DIR = srcs/utils/
UTILS_FILE = utils.c tuple_list.c promt.c
UTILS_SRC = $(addprefix $(UTILS_DIR), $(UTILS_FILE))

BUILDIN_DIR = srcs/buildin/
BUILDIN_FILE = ft_pwd.c
BUILDIN_SRC = $(addprefix $(BUILDIN_DIR), $(BUILDIN_FILE))

PARSER_DIR = srcs/parser/
PARSER_FILE =	parsing.c \
				parsing_utils_01.c \
				parsing_utils_02.c \
				msh_split.c
PARSER_SRC = $(addprefix $(PARSER_DIR), $(PARSER_FILE))

SRC = $(UTILS_SRC) $(INIT_SRC) $(BUILDIN_SRC) $(PARSER_SRC) ./srcs/minishell.c

OBJ = $(SRC:$(PATH_SRCS)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(PATH_SRCS)/%.c $(PATH_HEADER)
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	make -C $(PATH_LIBFT)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean :
	make clean -C $(PATH_LIBFT)
	@$(RM) $(OBJ_DIR)

fclean : clean
	make fclean -C $(PATH_LIBFT)
	@$(RM) $(NAME)

re : fclean all

.PHONY : re fclean clean all

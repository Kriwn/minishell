NAME = minishell
PATH_HEADER = includes
PATH_LIBFT = libft
PATH_SRCS = srcs
OBJ_DIR = objs

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(PATH_HEADER) -I$(PATH_LIBFT) -g
LDFLAGS = -L$(PATH_LIBFT) -lft -lreadline

RM = rm -rf

SRC = $(wildcard $(PATH_SRCS)/*.c)
OBJ = $(SRC:$(PATH_SRCS)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(PATH_SRCS)/%.c $(PATH_HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C $(PATH_LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean :
	@make clean -C $(PATH_LIBFT)
	@$(RM) $(OBJ_DIR)

fclean : clean
	@make fclean -C $(PATH_LIBFT)
	@$(RM) $(NAME)

re : fclean all

.PHONY : re fclean clean all

NAME = minishell

CC = cc -lreadline


CFLAGS = -g


SRC = tuple_list.c utils.c init.c main.c

%.o: %.c $(HEADER_FILE)
		$(CC) -c $(CFLAGS) $< -o $@

all : $(NAME)

clean :
	@ $(RM) $(OBJ)
fclean : clean
	@ $(RM) $(NAME)

re : fclean all

.PHONY : re fclean clean all

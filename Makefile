
NAME = minishell

SRCS = main.c signal.c utils.c parsing.c dollar.c linked_list.c lexer.c token.c \
exec.c pipe.c builtins/echo.c builtins/exec_builtins.c builtins/cd.c builtins/pwd.c \
builtins/env.c builtins/export.c parse_redir.c builtins/add_var_export.c builtins/unset.c\

CC = gcc -Wall -Wextra -Werror -g3

MY_OBJECTS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

LIB = -lreadline -L/Users/$$USER/.brew/opt/readline/lib

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I /Users/$$USER/.brew/opt/readline/include -c $< -o $(<:.c=.o)

$(NAME): $(MY_OBJECTS)
	$(MAKE) -C libft bonus
	$(CC) $(CFLAGS) $(MY_OBJECTS) $(LIB) $(LIBFT) -o $(NAME)

debug: $(MY_OBJECTS)
	$(MAKE) -C libft bonus
	$(CC) $(CFLAGS) $(MY_OBJECTS) $(LIB) -fsanitize=address $(LIBFT) -o $(NAME)

RM=rm -f

clean:
	$(RM) $(MY_OBJECTS)
	$(MAKE) -C libft clean

fclean: clean
	${RM} ${NAME}
	$(MAKE) -C libft fclean

re:	fclean all
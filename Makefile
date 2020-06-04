SRCS = *.c
NAME = gnl
FLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
		gcc $(FLAGS) $(SRCS) -o $(NAME)

clean:
		@/bin/rm -f $(NAME)

fclean: clean
		@/bin/rm -f $(NAME)

re: fclean all

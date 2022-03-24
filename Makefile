FLAGS=-Werror -Wextra -Wall -g
NAME=pipex
SRCS=*.c
INCLUDES=libft/libft.a
HEADER=pipex.h

all: $(NAME)

$(NAME): $(HEADER)	$(SRCS)
		make -C libft/
		cc $(SRCS) -o $(NAME) $(FLAGS) $(INCLUDES)

clean:
		@make -C libft/ clean

fclean: clean
		@rm -rf $(NAME)
		@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re bonus
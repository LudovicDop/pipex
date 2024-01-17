MAKEFLAGS += --silent
SRC = main.c parent.c child.c utils.c
CC = gcc -g -fsanitize=address
NAME = pipex

all : $(NAME)

$(NAME) :
	make -C libft/
	make -C gnl/
	$(CC) $(SRC) gnl/gnl.a -L./libft -lft -o $(NAME)
	echo "Done ✅"
clean :
	make clean -C libft/
	make clean -C gnl/
	echo "Cleaning has been carried out 🚮"
fclean :
	make fclean -C libft/
	make fclean -C gnl/
	rm -rf pipex
	echo "🚨Cleaning++ has been carried out 🚮🚨"
re : fclean all $(NAME)

.PHONY: all clean fclean re

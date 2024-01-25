MAKEFLAGS += --silent
SRC = main.c parent.c child.c utils.c utils_bis.c
CC = gcc -fsanitize=address -g3
NAME = pipex

all : $(NAME)

$(NAME) :
	make -C libft/
	$(CC) $(SRC) -L./libft -lft -o $(NAME)
	echo "Done ✅"
clean :
	make clean -C libft/
	echo "Cleaning has been carried out 🚮"
fclean :
	make fclean -C libft/
	rm -rf pipex
	echo "🚨Cleaning++ has been carried out 🚮🚨"
re : fclean all $(NAME)

.PHONY: all clean fclean re

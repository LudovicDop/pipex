MAKEFLAGS += --silent
SRC = main.c parent.c child.c utils.c utils_bis.c
CC = gcc -Wall -Werror -Wextra -g3
OBJ = $(SRC:.c=.o)
NAME = pipex

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft/
	$(CC) $(OBJ) -L./libft -lft -o $(NAME)
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

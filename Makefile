CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
NAME = cub
SRC = gnl_ut.c gnl.c main.c parse.c utiles.c parse_colors.c parse_textures.c valid_map.c allocate_free.c
OBJ = $(SRC:.c=.o)

all         : $(NAME)

$(NAME)     : $(OBJ)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o			:	%.c cub.h
			$(CC) $(FLAGS)  -c $< -o $@

clean       :
			@rm -f $(OBJ)

fclean      : clean
			@rm -f $(NAME)

re          : fclean all

.PHONY      : clean
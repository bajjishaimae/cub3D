NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -Imlx

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

SRCS = cub3d.c gnl_ut.c gnl.c main.c parse.c utiles.c parse_colors.c parse_textures.c valid_map.c allocate_free.c raycasting.c player.c 

HEADS = cub.h

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $^ -o $@

$(OBJS) : %.o: %.c $(HEADS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm	-f $(OBJS) $(OBJSB)

fclean : clean
	rm	-f $(NAME) $(BONUS)

re : fclean all

.PHONY : clean

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3D

MLX_ARCHIVE = MLX42/build/libmlx42.a

SRC = cub3d.c gnl_ut.c gnl.c initgame.c parse.c utiles.c parse_colors.c parse_textures.c valid_map.c allocate_free.c raycasting.c player.c moves.c window.c

OBJ = $(SRC:.c=.o)

all: mlx $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(MLX_ARCHIVE) -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(OBJ) -o $(NAME)

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<

mlx:
	@cd MLX42 && cmake -B build && cmake --build build -j4

clean:
	@rm -f $(OBJ)
	@if [ -d "MLX42/build" ]; then \
		cd MLX42/build && make clean; \
	fi

fclean: clean
	@rm -fr $(NAME) MLX42/build

re: fclean all

.PHONY: clean mlx


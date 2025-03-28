CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
NAME = cub3D

MLX_ARCHIVE = MLX42/build/libmlx42.a 

# MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

MLX_ARCHIVE = MLX42/build/libmlx42.a

SRC = cub3d.c gnl_ut.c gnl.c initgame.c parse.c utiles.c utiles2.c parse_colors.c parse_textures.c valid_map.c allocate_free.c raycasting.c  moves.c window.c minimap.c handle_keys.c animation.c

OBJS = $(SRC:.c=.o)

all: mlx $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(MLX_ARCHIVE) -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(OBJ) -o $(NAME)

all : mlx $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(MLX_ARCHIVE) -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -lm $^ -o $@
	@echo "\033[32mMaking Completed✅"

$(OBJS) : %.o: %.c $(HEADS) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

mlx:
	@cd MLX42 && cmake -B build && cmake --build build -j4

clean :
	@rm	-f $(OBJS)
	@if [ -d ".MLX42/build" ]; then \
		cd MLX42/build && make clean; \
    fi
	@echo "\033[0;33mCleaning Completed 🧼✨"

fclean : clean
	@rm	-f $(NAME) $(BONUS) .MLX42/build
	@echo "\033[0;31mRemoving Completed 🗑"

re : fclean all 

.PHONY : clean mlx
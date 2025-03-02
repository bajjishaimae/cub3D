NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -Imlx -g -fsanitize=address

# MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

MLX_ARCHIVE = MLX42/build/libmlx42.a

SRCS = cub3d.c gnl_ut.c gnl.c initgame.c parse.c utiles.c parse_colors.c parse_textures.c valid_map.c allocate_free.c raycasting.c player.c moves.c window.c

HEADS = cub.h

OBJS = $(SRCS:.c=.o)

all : mlx $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(MLX_ARCHIVE) -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -lm $^ -o $@
	@echo "\033[32mMaking Completed✅"

$(OBJS) : %.o: %.c $(HEADS) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

mlx:
	@cd MLX42 && cmake -B build && cmake --build build -j4

clean :
	@rm	-f $(OBJS) $(OBJSB)
	@if [ -d ".MLX42/build" ]; then \
		cd MLX42/build && make clean; \
    fi
	@echo "\033[0;33mCleaning Completed 🧼✨"

fclean : clean
	@rm	-f $(NAME) $(BONUS) .MLX42/build
	@echo "\033[0;31mRemoving Completed 🗑"

re : fclean all 

.PHONY : clean mlx

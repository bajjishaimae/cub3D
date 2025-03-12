/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:32:48 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/12 17:06:18 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	render_frame(void *param)
{
	t_data *data = (t_data *)param;
	raycast(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	// mini_map(data);
}

int main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		printf("Error\nyou need 1 file , .cub file\n");
		return (1);
	}
	check_file_ext(av[1]);
	parse(&data, av[1]);
	init_data(&data);
	init_player(&data);
	data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", false);
	data.img = mlx_new_image(data.mlx, data.screen_width, data.screen_height);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN);
	mlx_close_hook(data.mlx, ft_destroy_win, &data);
	mlx_key_hook(data.mlx, move, &data);
	mlx_cursor_hook(data.mlx, mouse_move, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}

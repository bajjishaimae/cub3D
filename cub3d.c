/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:32:48 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/02 17:47:50 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    put_player(t_data *data)
{
	int player_x;
	int player_y;
	int player_size;
	int x;
	int y;
	double scale_x;
	double scale_y;
	double scale;

	scale_x = (double)MINIMAP_WIDTH / (data->map_width * CELL_SIZE);
	scale_y = (double)MINIMAP_HEIGHT / (data->map_lenght * CELL_SIZE);
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	player_x = (int)(data->player.x_pos * CELL_SIZE * scale);
	player_y = (int)(data->player.y_pos * CELL_SIZE * scale);
	player_size = (CELL_SIZE / 8) * scale;
	x = -player_size;
	while (x <= player_size)
	{
		y = -player_size;
		while (y <= player_size)
		{
			put_pixel_to_image(data, player_x + x, player_y + y, 0x00FFFF);
			y++;
		}
		x++;
	}
}

int render_minimap(t_data *data)
{
	int		i;
	int		j;
	int		x;
	int		y;
	double	scale_x;
	double	scale_y;
	double	scale;

	scale_x = (double)MINIMAP_WIDTH / (data->map_width * CELL_SIZE);
	scale_y = (double)MINIMAP_HEIGHT / (data->map_lenght * CELL_SIZE);
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			y = 0;
			while (y < CELL_SIZE)
			{
				x = 0;
				while (x < CELL_SIZE)
				{
					data->pixel_x = j * CELL_SIZE + x;
					data->pixel_y = i * CELL_SIZE + y;
					if (data->map[i][j] == '1')
						put_pixel_to_image(data, data->pixel_x, data->pixel_y, 0xAAAAAA);
					else
						put_pixel_to_image(data, data->pixel_x, data->pixel_y, 0xFFFFFF);
					x++;
				}
				y++;
			}
			j++;
		}
	   i++;
	}
	put_player(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	return (0);
}

void	render_frame(void *param)
{
	t_data *data = (t_data *)param;
	raycast(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	render_minimap(data);
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
	mlx_close_hook(data.mlx, ft_destroy_win, &data);
	mlx_key_hook(data.mlx, move, &data);
	mlx_scroll_hook(data.mlx, mouse_move, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}

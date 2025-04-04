/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:26:13 by kelmounj          #+#    #+#             */
/*   Updated: 2025/04/04 14:59:19 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_player(t_data *data)
{
	int		player_x;
	int		player_y;
	int		player_size;
	int		x;
	int		y;

	player_x = (int)(data->player.x_pos * CELL_SIZE) \
		- (data->player.x_pos * CELL_SIZE - 100);
	player_y = (int)(data->player.y_pos * CELL_SIZE) \
		- (data->player.y_pos * CELL_SIZE - 100);
	(1) && (player_size = CELL_SIZE / 8, x = -player_size);
	while (x <= player_size)
	{
		y = -player_size;
		while (y <= player_size)
		{
			if (player_x + x >= 0 && player_y + y >= 0
				&& player_x + x < 200 && player_y + y < 200)
				put_pixel_to_image(data, player_x + x, \
						player_y + y, 0x00FFFF);
			y++;
		}
		x++;
	}
}

static void	minimap2(t_data *data, int i, int j)
{
	int	x;
	int	y;

	y = 0;
	while (y < CELL_SIZE)
	{
		x = 0;
		while (x < CELL_SIZE)
		{
			if (data->map[i][j] == 'D')
				put_pixel_to_image(data, data->m.tile_x + x - data->m.start_x,
					data->m.tile_y + y - data->m.start_y, 0x253342);
			else if (data->map[i][j] == 'A')
				put_pixel_to_image(data, data->m.tile_x + x - data->m.start_x,
					data->m.tile_y + y - data->m.start_y, 0xFF0000);
			else if (data->map[i][j] == '1')
				put_pixel_to_image(data, data->m.tile_x + x - data->m.start_x,
					data->m.tile_y + y - data->m.start_y, 0xAAAAAA);
			else
				put_pixel_to_image(data, data->m.tile_x + x - data->m.start_x,
					data->m.tile_y + y - data->m.start_y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	mini_map(t_data *data)
{
	int	i;
	int	j;

	data->m.player_x = (int)(data->player.x_pos * CELL_SIZE);
	data->m.player_y = (int)(data->player.y_pos * CELL_SIZE);
	(1) && (data->m.start_x = data->m.player_x - 100, data->m.start_y = \
	data->m.player_y - 100, data->m.end_x = data->m.player_x + 100, \
	data->m.end_y = data->m.player_y + 100);
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			data->m.tile_x = j * CELL_SIZE;
			data->m.tile_y = i * CELL_SIZE;
			if (data->m.tile_x + CELL_SIZE >= data->m.start_x
				&& data->m.tile_x <= data->m.end_x
				&& data->m.tile_y + CELL_SIZE >= data->m.start_y
				&& data->m.tile_y <= data->m.end_y)
				minimap2(data, i, j);
		}
	}
	put_player(data);
}

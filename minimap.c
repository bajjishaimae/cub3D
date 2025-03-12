/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:26:13 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/12 17:00:02 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_player(t_data *data)
{
	int player_x;
	int player_y;
	int player_size;
	int x;
	int y;
	
	player_x = (int)(data->player.x_pos * CELL_SIZE);
	player_y = (int)(data->player.y_pos * CELL_SIZE);
	player_size = CELL_SIZE / 8;
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

void	mini_map(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	player_x;
	int	player_y;
	int	start_x;
	int	start_y;
	int end_x;
	int	end_y;
	int	tile_x;
	int	tile_y;

	player_x = (int)(data->player.x_pos * CELL_SIZE);
	player_y = (int)(data->player.y_pos * CELL_SIZE);
	start_x = player_x - 50;
	start_y = player_y - 50;
	end_x = player_x + 50;
	end_y = player_y + 50;
	

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			tile_x = j * CELL_SIZE;
			tile_y = i * CELL_SIZE;
			if (tile_x + CELL_SIZE >= start_x && tile_x <= end_x && tile_y + CELL_SIZE >= start_y && tile_y <= end_y)
			{
				y = 0;
				while (y < CELL_SIZE)
				{
					x = 0;
					while (x < CELL_SIZE)
					{
							if (data->map[i][j] == '1')
								put_pixel_to_image(data, tile_x + x - start_x, tile_y + y - start_y, 0xAAAAAA);
							else
								put_pixel_to_image(data, tile_x + x - start_x, tile_y + y - start_y, 0xFFFFFF);
						x++;
					}
					y++;
				}
			}
			j++;
		}
		i++;
	}
	put_player(data);
}

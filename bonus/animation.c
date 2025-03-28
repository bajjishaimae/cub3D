/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:17:27 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/27 10:04:43 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void put_weapon(t_data *data)
{
	static int frame = 0;
	mlx_texture_t *texture;

	if (!data->is_animating)
		texture = data->frames[0];
	else
		texture = data->frames[frame];
	int weapon_height = texture->height * 0.5;
	int weapon_width = texture->width * 0.5;
	int start_x = data->screen_width / 2 - weapon_width / 2;
	int start_y = data->screen_height - weapon_height;

	int x = start_x;
	while (x < start_x + weapon_width)
	{
		double tex_x = (double)(x - start_x) / weapon_width * texture->width;
		int y = start_y;
		while (y < data->screen_height)
		{
			double tex_y = (double)(y - start_y) / weapon_height * texture->height;
			uint32_t tmp_value = (int)tex_y * texture->width + (int)tex_x;
			int index = tmp_value * 4;
			if (texture->pixels[index + 3] == 0)
			{
				y++;
				continue;
			}
			int color = color_from_pixel(texture, index);
			put_pixel_to_image(data, x, y, color);
			y++;
		}
		x++;
	}
	if (data->is_animating)
	{
		
		frame++;
		// if (frame == 7)
		// {
			
		// }
		if (frame >= 28)
		{
			frame = 0;
			data->is_animating = false;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 02:40:03 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/28 06:53:19 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    put_weapon(t_data *data)
{
	static int		frame = 0;
	mlx_texture_t	*texture;
	int				x;
	int				y;

	if (!data->is_animating)
		texture = data->frames[0];
	else
		texture = data->frames[frame];
	data->weapon.height = texture->height * 0.5;
	data->weapon.width = texture->width * 0.5;
	data->weapon.start_x = data->screen_width / 2 - data->weapon.width / 2;
	data->weapon.start_y = data->screen_height - data->weapon.height;

	x = data->weapon.start_x;
	while (x < data->weapon.start_x + data->weapon.width)
	{
		double tex_x = (double)(x - data->weapon.start_x) / data->weapon.width * texture->width;
		y = data->weapon.start_y;
		while (y < data->screen_height)
		{
			double tex_y = (double)(y - data->weapon.start_y) / data->weapon.height * texture->height;
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
		if (frame >= 28)
		{
			frame = 0;
			data->is_animating = false;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:27:33 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/21 14:05:55 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_dist(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->sprite_n)
	{
		data->sprites[i].dist = ((data->player.x_pos - data->sprites[i].sprite_x) * (data->player.x_pos - data->sprites[i].sprite_x)) +
			((data->player.y_pos - data->sprites[i].sprite_y) * (data->player.y_pos - data->sprites[i].sprite_y));
		i++;
	}
}

void	sort_sprite(t_data * data)
{
	int			i;
	int			j;
	t_sprite	tmp;

	set_dist(data);
	i = 0;
	while (i < data->sprite_n)
	{
		j = 0;
		while (j < data->sprite_n - i - 1)
		{
			if (data->sprites[j].dist < data->sprites[j + 1].dist)
			{
				tmp = data->sprites[j + 1];
				data->sprites[j + 1] = data->sprites[j];
				data->sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	trans_sprite(t_data *data)
{
	int		i;
	double	x_sprt;
	double	y_sprt;
	double	trans_x;
	double	trans_y;
	double	invrs;

	sort_sprite(data);
	i = 0;
	while (i < data->sprite_n)
	{
		x_sprt = data->sprites[i].sprite_x - data->player.x_pos;
		y_sprt = data->sprites[i].sprite_y - data->player.y_pos;
		invrs = 1 / (data->player.plane_x * data->player.y_dir - data->player.x_dir * data->player.plane_y);
		trans_x = invrs * data->player.y_dir * x_sprt - data->player.x_dir * y_sprt;
		trans_y = invrs * (-data->player.plane_y * x_sprt + data->player.plane_x * y_sprt);
		data->sprites[i].sprite_sc_x = (SCREEN_WIDTH / 2) * (1 + trans_x / trans_y);
		data->sprites[i].sprite_h = fabs(SCREEN_HEIGHT / trans_y);
		i++;
	}
	draw_sprite(data);
}

void	draw_sprite(t_data *data)
{
	data->sprites->sprite_w = data->sprites->sprite_h;
	data->sprites->draw_sx = data->sprites->sprite_sc_x - data->sprites->sprite_w / 2 ;
	data->sprites->draw_ex = data->sprites->sprite_sc_x + data->sprites->sprite_w / 2;
	data->sprites->draw_sy = SCREEN_HEIGHT / 2 - data->sprites->sprite_h;
	data->sprites->draw_ey = SCREEN_HEIGHT / 2 + data->sprites->sprite_h;
	put_texture_sprite(data);
}

void	put_texture_sprite(t_data *data)
{
	mlx_texture_t *texture;
	int	stripe;
	int	y;
	int	d;

	texture = data->sprite;
	stripe = data->sprites->draw_sx;
	while (stripe < data->sprites->draw_ex)
	{
		data->sprites->tex_x = (int)((stripe - (-data->sprites->sprite_w / 2 + data->sprites->sprite_sc_x)) * texture->width / data->sprites->sprite_w);
		if (stripe >= 0 && stripe < SCREEN_WIDTH && data->sprites->dist < data->zbuffer[stripe])
			break;
		y = data->sprites->draw_sy;
		while (y < data->sprites->draw_ey)
		{
			d = y * 256 - SCREEN_HEIGHT * 128 + data->sprites->sprite_h * 128;
			data->sprites->tex_y = ((d * texture->height) / data->sprites->sprite_h) / 256;
			data->sprites->tex_x = fmin(fmax(data->sprites->tex_x, 0), texture->width - 1);
			data->sprites->tex_y = fmin(fmax(data->sprites->tex_y, 0), texture->height - 1);
			int tmp = data->sprites->tex_y * texture->width + data->sprites->tex_x;
			int index = tmp * 4;
			int color = color_from_pixel(texture, index);
			// if (color ==  0x000000)
			// {
			// 	break;
			// }
			put_pixel_to_image(data, stripe, y, color);
			y++;
		}
		stripe++;
	}
}

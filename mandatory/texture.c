/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:17:04 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/25 03:43:45 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void put_pixel_to_image(t_data *data, int x, int y, int color)
{
	if(x >= 0 && x < data->screen_width && y >= 0 && y < data->screen_height)
		mlx_put_pixel(data->img, x, y, color);
}

int	color_from_pixel(mlx_texture_t *texture, int index)
{
	int	r;
	int	g;
	int	b;

	r = texture->pixels[index];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	return (convert_rgb(r, g, b));
}

void	ft_put_pixel(t_data *data, uint32_t x,
	uint32_t y, uint32_t color)
{
	if (x >= 0 && x < (uint32_t)data->screen_width && y >= 0 && y < (uint32_t)data->screen_height)
		mlx_put_pixel(data->img, x, y, color);
}


void put_texture(t_data *data, int end_line, int start_line, int x)
{
	mlx_texture_t *texture = get_wall_texture(data);
	int tmp_start = start_line;
	int tmp_end = end_line;

	data->tex_pos_x *= texture->width;

	if (data->side_wall == 1 && data->ray.rayd_y < 0)
		data->tex_pos_x = texture->width - data->tex_pos_x - 1;

	while (start_line < end_line)
	{
		data->tex_pos_y = (start_line - tmp_start) / (double)(tmp_end - tmp_start);
		data->tex_pos_y *= texture->height;

		uint32_t tmp_value = (int)data->tex_pos_y * texture->width;
		tmp_value += (int)data->tex_pos_x;
		int index = tmp_value * 4;

		int color = color_from_pixel(texture, index);
		put_pixel_to_image(data, x, start_line, color);

		start_line++;
	}
}

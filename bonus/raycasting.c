/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:32:41 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/20 18:01:36 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

void	raycast(t_data *data)
{
	double	camera_x;
	int		i;

	i = 0;
	while (i < data->screen_width)
	{
		camera_x = 2 * i / (double)data->screen_width - 1;
		data->ray.rayd_x = data->player.x_dir + data->player.plane_x * camera_x;
		data->ray.rayd_y = data->player.y_dir  + data->player.plane_y * camera_x;
		init_dist(data, i);
		i++;
	}
}

void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	if(x >= 0 && x < data->screen_width && y >= 0 && y < data->screen_height)
		mlx_put_pixel(data->img, x, y, color);
}

void	draw_ceiling(t_data *data,int start_line, int x, int color)
{
	int	y;

	y = start_line;
	while (y >= 0)
	{
		put_pixel_to_image(data, x ,y, color);
		y--;
	}
}
void	draw_floor(t_data *data,int end_line, int x, int color)
{
	int y;

	y = end_line + 1;
	while (y <= data->screen_height)
	{
		put_pixel_to_image(data, x, y, color);
		y++;
	}
}

double	distance(int x1, int y1, int x2, int y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	check_doors(t_data *data)
{
	int i = 0;
	while (i < data->n_of_doors)
	{
		double dist = distance(data->player.x_pos, data->player.y_pos, data->doors[i].x, data->doors[i].y);
		if (dist < DOOR_OPEN_DIST)
			data->doors[i].is_open = 1;
		else
			data->doors[i].is_open = 0;
		i++;
	}
}

void	draw_line(t_data *data, double perpWallDist, int x)
{
	data->line_h = (int)(data->screen_height / perpWallDist);
	data->start_line = -data->line_h / 2 + data->screen_height / 2;
	if (data->start_line < 0)
		data->start_line = 0;
	data->end_line = data->line_h / 2 + data->screen_height / 2;
	if (data->end_line >= data->screen_height)
		data->end_line = data->screen_height - 1;

	draw_ceiling(data, data->start_line, x, convert_rgb(data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]));
	put_texture(data, data->end_line, data->start_line, x);
	draw_floor(data, data->end_line, x, convert_rgb(data->floor_color[0], data->floor_color[1], data->floor_color[2]));
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


void	put_texture(t_data *data, int end_line, int start_line, int x)
{
	mlx_texture_t *texture;
	int tmp_start = start_line;
	int tmp_end = end_line;

    if (data->hit_door)
        texture = data->door;
    else if(data->hit_sprite)
        texture = data->sprite;
    else 
        texture = get_wall_texture(data);
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

t_door *find_which_door(t_data *data, int x, int y)
{
	int i = 0;
	while (i < data->n_of_doors)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return &data->doors[i];
		i++;
	}
	return NULL;
}

void	raytrace(t_data *data, int map_x, int map_y, int x)
{
    data->hit_door = 0;
    data->hit_sprite = 0;
    bool hit_wall = 0;
    double perpWallDist = 0.0;
    int side_wall = -1;

    while (hit_wall == 0)
    {
        if (data->ray.side_x < data->ray.side_y)
        {
            data->ray.side_x += data->ray.delta_x;
            map_x += data->ray.step_x;
            side_wall = 0;
        }
        else
        {
            data->ray.side_y += data->ray.delta_y;
            map_y += data->ray.step_y;
            side_wall = 1;
        }
        if (map_x < 0 || map_x >= data->map_width || map_y < 0 || map_y >= data->map_lenght)
        {
            hit_wall = 1;
            break;
        }
        if (data->map[map_y][map_x] == '1' || data->map[map_y][map_x] == 'D' ||  data->map[map_y][map_x] == 'A')
        {
            if (data->map[map_y][map_x] == 'D')
            {
                t_door *door = find_which_door(data, map_x, map_y);
                if (door && !door->is_open)
                {
                    hit_wall = 1;
                    data->hit_door = 1;
                }
            }
            else if(data->map[map_y][map_x] == 'A')
            {
                data->hit_sprite = 1;
                hit_wall = 1;
            }
            else
                hit_wall = 1;
        }
    }
    data->ray.map_x = map_x;
    data->ray.map_y = map_y;
    if (side_wall == 0)
    {
        perpWallDist = data->ray.side_x - data->ray.delta_x;
        data->tex_pos_x = data->player.y_pos + perpWallDist * data->ray.rayd_y;
    }
    else
    {
        perpWallDist = data->ray.side_y - data->ray.delta_y;
        data->tex_pos_x = data->player.x_pos + perpWallDist * data->ray.rayd_x;
    }
    data->tex_pos_x -= floor(data->tex_pos_x);
    data->side_wall = side_wall;
    draw_line(data, perpWallDist, x);
}

void	init_dist(t_data *data, int x)
{
	int		map_x;
	int		map_y;

	map_x = (int)data->player.x_pos;
	map_y = (int)data->player.y_pos;
	if (data->ray.rayd_x == 0)
		data->ray.delta_x = INF;
	else
		data->ray.delta_x = fabs(1 / data->ray.rayd_x);
	if (data->ray.rayd_y == 0)
		data->ray.delta_y = INF;
	else
		data->ray.delta_y = fabs(1 / data->ray.rayd_y);
	if (data->ray.rayd_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_x = (data->player.x_pos - map_x) * data->ray.delta_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_x = (map_x + 1 - data->player.x_pos) * data->ray.delta_x;
	}
	if (data->ray.rayd_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_y = (data->player.y_pos - map_y) * data->ray.delta_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_y = (map_y + 1 - data->player.y_pos) * data->ray.delta_y;
	}
	raytrace(data, map_x, map_y, x);
}

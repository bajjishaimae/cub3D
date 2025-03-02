/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:02:53 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/02 17:55:45 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int move_up(t_data *data, double move_speed)
{
	double x_next;
	double y_next;

	x_next = (data->player.x_pos + data->player.x_dir * move_speed);
	y_next = (data->player.y_pos + data->player.y_dir * move_speed);
	if ((int)x_next >= 0 && (int)x_next < data->map_width && (int)y_next >= 0 &&
		(int)y_next < data->map_lenght && data->map[(int)(y_next + 0.1)][(int)(x_next + 0.1)] != '1' &&
		data->map[(int)(y_next - 0.1)][(int)(x_next - 0.1)] != '1')
	{
		data->player.x_pos += data->player.x_dir * move_speed;
		data->player.y_pos += data->player.y_dir * move_speed;
	}
	return (1);
}

int move_down(t_data *data, double move_speed)
{
	int x_next;
	int y_next;

	x_next = (data->player.x_pos - data->player.x_dir * move_speed);
	y_next = (data->player.y_pos - data->player.y_dir * move_speed);
	if ((int)x_next >= 0 && (int)x_next < data->map_width && (int)y_next >= 0 &&
		(int)y_next < data->map_lenght && data->map[(int)(y_next + 0.1)][(int)(x_next + 0.1)] != '1')
	{
		data->player.x_pos -= data->player.x_dir * move_speed;
		data->player.y_pos -= data->player.y_dir * move_speed;
	}
	return (1);
}

int move_right(t_data *data, double move_speed)
{
	double x_next = data->player.x_pos + data->player.plane_x * move_speed;
	double y_next = data->player.y_pos + data->player.plane_y * move_speed;

	if (data->map[(int)data->player.y_pos][(int)x_next] != '1')
		data->player.x_pos += data->player.plane_x * move_speed;
	if (data->map[(int)y_next][(int)data->player.x_pos] != '1')
		data->player.y_pos += data->player.plane_y * move_speed;

	return (1);
}


int move_left(t_data *data, double move_speed)
{
	double x_next = data->player.x_pos - data->player.plane_x * move_speed;
	double y_next = data->player.y_pos - data->player.plane_y * move_speed;

	if (data->map[(int)data->player.y_pos][(int)x_next] != '1')
		data->player.x_pos -= data->player.plane_x * move_speed;
	if (data->map[(int)y_next][(int)data->player.x_pos] != '1')
		data->player.y_pos -= data->player.plane_y * move_speed;

	return (1);
}

int rot_left(t_data *data, double rot_speed)
{
	double  old_dirx;
	double  old_planex;

	old_dirx = data->player.x_dir;
	old_planex = data->player.plane_x;

	data->player.x_dir = data->player.x_dir * cos(-rot_speed) - data->player.y_dir * sin(-rot_speed);
	data->player.y_dir = old_dirx * sin(-rot_speed) + data->player.y_dir * cos(-rot_speed);
	data->player.plane_x = data->player.plane_x * cos(-rot_speed) - data->player.plane_y * sin(-rot_speed);
	data->player.plane_y = old_planex * sin(-rot_speed) + data->player.plane_y * cos(-rot_speed);
	return (1);
}

int rot_right(t_data *data, double rot_speed)
{
double  old_dirx;
	double  old_planex;
	
	old_dirx = data->player.x_dir;
	old_planex = data->player.plane_x;

	data->player.x_dir = data->player.x_dir * cos(rot_speed) - data->player.y_dir * sin(rot_speed);
	data->player.y_dir = old_dirx * sin(rot_speed) + data->player.y_dir * cos(rot_speed);
	data->player.plane_x = data->player.plane_x * cos(rot_speed) - data->player.plane_y * sin(rot_speed);
	data->player.plane_y = old_planex * sin(rot_speed) + data->player.plane_y * cos(rot_speed);
	return (1);
}

int move_to(keys_t keydata, t_data *data, double move_speed, double rot_speed)
{
	if (keydata == MLX_KEY_RIGHT)
	{
		rot_right(data, rot_speed);
	}
	if (keydata == MLX_KEY_LEFT)
	{
		rot_left(data, rot_speed);
	}
	if (keydata == MLX_KEY_D)
	{
		move_right(data, move_speed);
	}
	if (keydata == MLX_KEY_A)
	{
		move_left(data, move_speed);
	}
	if (keydata == MLX_KEY_W)
	{
		move_up(data, move_speed);
	}
	if (keydata == MLX_KEY_S)
	{
		move_down(data, move_speed);
	}
	if (keydata == MLX_KEY_ESCAPE)
	{
		// mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		exit (0);
	}
	// mlx_destroy_image(data->mlx_ptr, data->img.img);
	data->img = mlx_new_image(data->mlx, data->screen_width, data->screen_height);
	render_frame(data);
	render_minimap(data);
	return (1);
}

// size_t	get_tv(void)
// {
// 	struct timeval	tv;
// 	size_t			res;

// 	if (gettimeofday(&tv, NULL) == -1)
// 		write(2, "Error in time\n", 14);
// 	res = tv.tv_usec / 1000 + tv.tv_sec * 1000;
// 	return (res);
// }

	// printf("mouse mouvement x: %d\ty: %d\n", x, y);
	// mlx_mouse_hide();

	
void	mouse_move(double x, double y, void *param)
{
	static int	last_x = -1;
	double		old_dirx;
	double		old_planex;
	double		rot_speed;
	
	t_data *data = (t_data *)param;
	if (last_x < 0 || last_x > data->screen_width || y > data->screen_height || y < 0)
	{
		last_x = x;
		return ;
	}
	old_dirx = data->player.x_dir;
	old_planex = data->player.plane_x;

	rot_speed = SPEED_ROT / 2;
	if (last_x > x)
	{
		data->player.x_dir = data->player.x_dir * cos(-rot_speed) - data->player.y_dir * sin(-rot_speed);
		data->player.y_dir = old_dirx * sin(-rot_speed) + data->player.y_dir * cos(-rot_speed);
		data->player.plane_x = data->player.plane_x * cos(-rot_speed) - data->player.plane_y * sin(-rot_speed);
		data->player.plane_y = old_planex * sin(-rot_speed) + data->player.plane_y * cos(-rot_speed);
	}
	else
	{
		data->player.x_dir = data->player.x_dir * cos(rot_speed) - data->player.y_dir * sin(rot_speed);
		data->player.y_dir = old_dirx * sin(rot_speed) + data->player.y_dir * cos(rot_speed);
		data->player.plane_x = data->player.plane_x * cos(rot_speed) - data->player.plane_y * sin(rot_speed);
		data->player.plane_y = old_planex * sin(rot_speed) + data->player.plane_y * cos(rot_speed);
	}
	last_x = x;
}

void	move(mlx_key_data_t keydata, void *param)
{
	t_data *data = (t_data *)param;
	move_to(keydata.key, data, SPEED_MOVE, SPEED_ROT);
}

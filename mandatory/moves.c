/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:02:53 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/20 17:01:44 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	move_up(t_data *data, double move_speed)
{
	double	x_next;
	double	y_next;

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

int	move_down(t_data *data, double move_speed)
{
	int	x_next;
	int	y_next;

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

int	move_right(t_data *data, double move_speed)
{
	double	x_next;
	double	y_next;

	x_next = data->player.x_pos + data->player.plane_x * move_speed;
	y_next = data->player.y_pos + data->player.plane_y * move_speed;
	if (data->map[(int)data->player.y_pos][(int)x_next] != '1')
		data->player.x_pos += data->player.plane_x * move_speed;
	if (data->map[(int)y_next][(int)data->player.x_pos] != '1')
		data->player.y_pos += data->player.plane_y * move_speed;

	return (1);
}


int	move_left(t_data *data, double move_speed)
{
	double	x_next;
	double	y_next;

	x_next = data->player.x_pos - data->player.plane_x * move_speed;
	y_next = data->player.y_pos - data->player.plane_y * move_speed;
	if (data->map[(int)data->player.y_pos][(int)x_next] != '1')
		data->player.x_pos -= data->player.plane_x * move_speed;
	if (data->map[(int)y_next][(int)data->player.x_pos] != '1')
		data->player.y_pos -= data->player.plane_y * move_speed;

	return (1);
}

int	rot_left(t_data *data, double rot_speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->player.x_dir;
	old_planex = data->player.plane_x;

	data->player.x_dir = data->player.x_dir * cos(-rot_speed) - data->player.y_dir * sin(-rot_speed);
	data->player.y_dir = old_dirx * sin(-rot_speed) + data->player.y_dir * cos(-rot_speed);
	data->player.plane_x = data->player.plane_x * cos(-rot_speed) - data->player.plane_y * sin(-rot_speed);
	data->player.plane_y = old_planex * sin(-rot_speed) + data->player.plane_y * cos(-rot_speed);
	return (1);
}

int	rot_right(t_data *data, double rot_speed)
{
	double	old_dirx;
	double	old_planex;
	
	old_dirx = data->player.x_dir;
	old_planex = data->player.plane_x;

	data->player.x_dir = data->player.x_dir * cos(rot_speed) - data->player.y_dir * sin(rot_speed);
	data->player.y_dir = old_dirx * sin(rot_speed) + data->player.y_dir * cos(rot_speed);
	data->player.plane_x = data->player.plane_x * cos(rot_speed) - data->player.plane_y * sin(rot_speed);
	data->player.plane_y = old_planex * sin(rot_speed) + data->player.plane_y * cos(rot_speed);
	return (1);
}

void	move_to(void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (data->key.right)
		rot_right(data, SPEED_ROT);
	if (data->key.left)
		rot_left(data, SPEED_ROT);
	if (data->key.d)
		move_right(data, SPEED_MOVE);
	if (data->key.a)
		move_left(data, SPEED_MOVE);
	if (data->key.w)
		move_up(data, SPEED_MOVE);
	if (data->key.s)
		move_down(data, SPEED_MOVE);
}

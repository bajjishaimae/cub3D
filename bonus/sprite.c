/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:27:33 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/13 18:18:01 by kelmounj         ###   ########.fr       */
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

	i = 0;
	while (i < data->sprite_n)
	{
		j = 0;
		while (j < data->sprite_n - i)
		{
			if (data->sprites[j].dist > data->sprites[j + 1].dist)
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
	int	i;
	double	x_sprt;
	double	y_sprt;

	i = 0;
	while (i < data->sprite_n)
	{
		x_sprt = data->sprites[i].sprite_x - data->player.x_pos;
		y_sprt = data->sprites[i].sprite_y - data->player.y_pos;
		i++;
	}
	
}
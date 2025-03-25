/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:25:32 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/25 04:07:52 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_destroy_win(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_close_window(data->mlx);
}

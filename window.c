/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:25:32 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/02 17:38:30 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_destroy_win(void *param)
{
	t_data *data = (t_data *)param;
	mlx_terminate(data->mlx);
	exit (0);
}
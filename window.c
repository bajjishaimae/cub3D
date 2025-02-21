/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:25:32 by kelmounj          #+#    #+#             */
/*   Updated: 2025/02/21 12:29:36 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int    ft_destroy_win(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    exit (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 07:11:15 by kelmounj          #+#    #+#             */
/*   Updated: 2025/03/25 07:12:26 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	int	get_lenght(long nb)
{
	int		count;

	count = 0;
	if (nb < 0)
	{
		count++;
		nb = nb * (-1);
	}
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	count++;
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nb;

	nb = n;
	len = get_lenght(nb);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (nb < 0)
		nb = -nb;
	while (len >= 0)
	{
		if (n < 0 && len == 0)
		{
			str[len] = '-';
			break ;
		}
		str[len] = (nb % 10) + 48;
		nb = nb / 10;
		len--;
	}
	return (str);
}

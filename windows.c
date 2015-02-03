/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 10:38:16 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/03 14:15:40 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	draw(t_e point)
{
	int y;
	int x;

	y = 0;
	while (y != point.y)
	{
		x = -1;
		while (++x != point.x)
			mlx_pixel_put(point.mlx, point.win, point.map[y][x].x * 50 + 100, point.map[y][x].y * 50 +100, 0xFF0000);
		y++;
	}
}

int	expose_hook(t_e *e)
{
	draw(*e);
	return (0);
}

void	window(t_e	point)
{
	point.mlx = mlx_init();
	point.win = mlx_new_window(point.mlx, 1000, 1000, "42");
	mlx_expose_hook(point.win, expose_hook, &point);
	mlx_key_hook(point.win, key_hook, &point);
	mlx_loop(point.mlx);
	
/*
**  mlx_loop(point.mlx);
**  pour linstant loop en commantaire
*/

}

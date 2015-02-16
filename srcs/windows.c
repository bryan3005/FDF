/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 10:38:16 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/15 23:56:07 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw(t_e e)
{
	int y;
	int x;

	y = 0;
	while (y != e.y)
	{
		x = -1;
		while (++x != e.x)
		{
			if (x != e.x - 1 && (is_in_map(e, x, y) || is_in_map(e, x + 1, y)))
				draw_line(e, e.map[y][x], e.map[y][x + 1]);
			if (y != e.y - 1 && (is_in_map(e, x, y) || is_in_map(e, x, y + 1)))
				draw_line(e, e.map[y][x], e.map[y + 1][x]);
		}
		y++;
	}
}

int		expose_hook(t_e *e)
{
	draw(*e);
	return (0);
}

void	zoom_2(t_e *e, int x, int y)
{
	e->angle1 = (sin(e->decala * M_PI / 180));
	e->angle2 = (cos(e->decala * M_PI / 180));
	// if (e->proj == 0)
	// {
	// 	e->map[y][x].y = y * e->zoom + e->decaly - e->zoom1 *
	// 	e->zoom * e->map[y][x].z;
	// 	e->map[y][x].x = x * e->zoom + e->decalx - e->zoom1 *
	// 	e->zoom * e->map[y][x].z;
	// }
	// else if (e->proj == 1)
	// {
		e->map[y][x].y = ((x * e->zoom - e->zoom1 *
		e->zoom * e->map[y][x].z) * e->angle1) + e->decaly +
		((y * e->zoom - e->zoom1 *
		e->zoom * e->map[y][x].z) * e->angle2) ;
		e->map[y][x].x = ((x * e->zoom  - e->zoom1 *
		e->zoom * e->map[y][x].z) * e->angle2) + e->decalx -
		((y * e->zoom  - e->zoom1 *
		e->zoom * e->map[y][x].z) * e->angle1);
	// }
}

t_e		zoom(t_e e)
{
	int		y;
	int		x;

	y = 0;
	while (y != e.y)
	{
		x = -1;
		while (++x != e.x)
			zoom_2(&e, x, y);
		y++;
	}
	return (e);
}

void	window(t_e e)
{
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, e.win_x, e.win_y, "42");
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_hook(e.win, 2, 3, key_hook, &e);
	mlx_loop(e.mlx);
}

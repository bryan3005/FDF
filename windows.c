/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 10:38:16 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/09 13:04:49 by mbryan           ###   ########.fr       */
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
			if (x != e.x - 1 && e.map[y][x].x <= 1000 && e.map[y][x].y <= 1000)
				draw_x(e.map[y][x], e.map[y][x + 1], e);
			if (y != e.y - 1 && e.map[y][x].x <= 1000 && e.map[y][x].y <= 1000)
				draw_y(e.map[y][x], e.map[y + 1][x], e);
		}
		y++;
	}
}

int	expose_hook(t_e *e)
{
	draw(*e);
	return (0);
}

t_e		zoom(t_e e, int param)
{
	int y;
	int x;
	(void)param;
	// e.zoom = e.zoom + (param * 2);
	y = 0;
	while (y != e.y)
	{
		x = -1;
		while (++x != e.x)
		{
			e.map[y][x].y = y * e.zoom + e.decaly - e.zoom1 * e.zoom *e.map[y][x].z;
			e.map[y][x].x = x * e.zoom + e.decalx - e.zoom1 * e.zoom * e.map[y][x].z;
		}
		y++;
	}
	return (e);
}

int		key_hook(int keycode, t_e *e)
{
	ft_putstr("Key :");
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 65307)
		exit(0);
	if (keycode == 114)
		{
			*e = initiate(*e);
			*e = zoom(*e, 0);
		}	
	if (keycode == 117)	
		*e = zoom(*e, e->zoom1 = e->zoom1 + 0.025);
	if (keycode == 100)
		*e = zoom(*e, e->zoom1 = e->zoom1 - 0.025);
	if (keycode == 65451 || keycode == 61)
		*e = zoom(*e, e->zoom = e->zoom + 0.5);
	if ((keycode == 65453 || keycode == 45) && e->zoom > 0.5)
		*e = zoom(*e, e->zoom = e->zoom - 0.5);
	if (keycode == 65362)
		*e = zoom(*e, e->decaly = e->decaly - 10);
	if (keycode == 65364)
		*e = zoom(*e, e->decaly = e->decaly + 10);
	if (keycode == 65361)
		*e = zoom(*e, e->decalx = e->decalx - 10);
	if (keycode == 65363)
		*e = zoom(*e, e->decalx = e->decalx + 10);
	mlx_clear_window(e->mlx, e->win);
	draw(*e);
	return (0);
}

void	window(t_e	e)
{
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 1000, 1000, "42");
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_hook(e.win, 2, 3, key_hook, &e);
	mlx_loop(e.mlx);
}

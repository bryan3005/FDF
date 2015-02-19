/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 10:34:19 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/19 17:01:20 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
void	check_for_bad_length(int x)
{
	static int		nbcount = 0;
	static int		stat = 0;

	if (stat == 0)
	{
		nbcount = x;
		stat++;
	}
	if (nbcount != x && nbcount != 0)
	{
		ft_putendl("bad length");
		exit(EXIT_FAILURE);
	}
}

void	check_for_gnl_error(int ret)
{
	if (ret == -1)
	{
		ft_putendl("Error : get_next_line");
		exit(EXIT_FAILURE);
	}
}

void	keycode1(int keycode, t_e *e)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 114)
	{
		*e = initiate(*e);
		*e = zoom(*e);
	}
	if (keycode == 117)
		e->zoom1 = e->zoom1 + 0.025;
	if (keycode == 112)
		e->decala += 5;
	if (keycode == 105)
		e->decala -= 5;
}

int		key_hook(int key, t_e *e)
{
	keycode1(key, e);
	if (key == 100)
		e->zoom1 = e->zoom1 - 0.025;
	if ((key == 65451 || key == 61) && e->zoom < 50000)
		e->zoom = e->zoom + e->zoom / 5;
	if ((key == 65453 || key == 45) && e->zoom > 0.1)
		e->zoom = e->zoom - e->zoom / 5;
	if (key == 65362)
		e->decaly = e->decaly - 10;
	if (key == 65364)
		e->decaly = e->decaly + 10;
	if (key == 65361)
		e->decalx = e->decalx - 10;
	if (key == 65363)
		e->decalx = e->decalx + 10;
	if (key == 117 || key == 100 || key == 65451 || key == 61 ||
		key == 65453 || key == 45 || key == 65362 || key == 65364 ||
		key == 65361 || key == 65363 || key == 114 ||
		key == 112 || key == 105)
	{
		*e = zoom(*e);
		mlx_clear_window(e->mlx, e->win);
		draw(*e);
	}
	return (0);
}

int		is_in_map(t_e e, int x, int y)
{
	if (e.map[y][x].x > e.win_x || e.map[y][x].x < 0)
		return (0);
	if (e.map[y][x].y > e.win_y || e.map[y][x].y < 0)
		return (0);
	return (1);
}

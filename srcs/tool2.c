/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 14:27:11 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/19 13:57:07 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_e		put_y(t_e point, int y)
{
	int i;
	int j;

	point.y = y;
	i = point.y;
	point.valide = 1;
	point = initiate(point);
	while (i-- != 0)
	{
		j = point.x;
		while (j-- != 0)
			point.map[i][j].y = point.map[i][j].y * point.zoom + point.decaly -
			point.zoom1 * point.zoom * point.map[i][j].z;
	}
	zoom(point);
	return (point);
}

void	color_me(t_e e, int x, int y, int z)
{
	if (z > 0)
		mlx_pixel_put(e.mlx, e.win, x, y, 0xff0000);
	else if (z == 0)
		mlx_pixel_put(e.mlx, e.win, x, y, 0xffffff);
	else
		mlx_pixel_put(e.mlx, e.win, x, y, 0x003366);
}

void	draw_y(t_get p1, t_get p2, t_e e, double a)
{
	double	b;
	double	ret;

	b = p1.y - a * p1.x;
	while (p1.y != p2.y)
	{
		if (p2.x - p1.x != 0)
		{
			ret = p1.y - b;
			ret /= a;
		}
		else
			ret = p1.x;
		p1.z = (p1.z > p2.z) ? p1.z : p2.z;
		color_me(e, ret, p1.y, p1.z);
		(p1.y > p2.y) ? p1.y-- : p1.y++;
	}
}

void	draw_x(t_get p1, t_get p2, t_e e, double a)
{
	double	b;
	double	ret;

	ret = 0;
	b = p1.y - a * p1.x;
	while (p1.x != p2.x)
	{
		ret = a * p1.x + b;
		p1.z = (p1.z > p2.z) ? p1.z : p2.z;
		color_me(e, p1.x, ret, p1.z);
		(p1.x > p2.x) ? p1.x-- : p1.x++;
	}
}

void	draw_line(t_e e, t_get p1, t_get p2)
{
	double	a;
	double	dx;
	double	dy;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (dx != 0)
		a = dy / dx;
	else
		a = 0;
	draw_y(p1, p2, e, a);
	draw_x(p1, p2, e, a);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 14:27:11 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/13 10:35:16 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_e		put_y(t_e point, int y)
{
	int i;
	int j;

	point.y = y;
	i = point.y;
	point = initiate(point);
	while (i-- != 0)
	{
		j = point.x;
		while (j-- != 0)
			point.map[i][j].y = point.map[i][j].y * point.zoom + point.decaly -
			point.zoom1 * point.zoom * point.map[i][j].z;
	}
	return (point);
}

void	check_for_gnl_error(int ret)
{
	if (ret == -1)
	{
		ft_putendl("Error : get_next_line");
		exit(EXIT_FAILURE);
	}
}

t_get	color_me(double ret, t_get p1, t_get p2, t_e e)
{
	if (p1.z > 0 || p2.z > 0)
		mlx_pixel_put(e.mlx, e.win, ret, p1.y, 0xff0000);
	else if (p1.z == 0 || p2.z == 0)
		mlx_pixel_put(e.mlx, e.win, ret, p1.y, 0xffffff);
	else
		mlx_pixel_put(e.mlx, e.win, ret, p1.y, 0x4595FF);
	p1.y++;
	return (p1);
}

void	draw_y(t_get p1, t_get p2, t_e e)
{
	double	a;
	double	b;
	double	dx;
	double	dy;
	double	ret;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	ret = 0;
	if (dx != 0)
		a = dy / dx;
	else
		a = 0;
	b = p1.y - a * p1.x;
	while (p1.y < p2.y)
	{
		if (dx != 0)
		{
			dy = p1.y - b;
			ret = dy / a;
		}
		else
			ret = p1.x;
		p1 = color_me(ret, p1, p2, e);
	}
}

void	draw_x(t_get p1, t_get p2, t_e e)
{
	double	a;
	double	b;
	double	dx;
	double	dy;
	double	ret;

	ret = 0;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (dx != 0)
		a = dy / dx;
	else
		a = 0;
	b = p1.y - a * p1.x;
	while (p1.x < p2.x)
	{
		ret = a * p1.x + b;
		if ((p1.z > 0 || p2.z > 0))
			mlx_pixel_put(e.mlx, e.win, p1.x, ret, 0xff0000);
		else if (p1.z == 0 || p2.z == 0)
			mlx_pixel_put(e.mlx, e.win, p1.x, ret, 0xffffff);
		else
			mlx_pixel_put(e.mlx, e.win, p1.x, ret, 0x4595FF);
		p1.x++;
	}
}

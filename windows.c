/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 10:38:16 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/03 12:08:06 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	make_point(t_get **get_line, t_e point)
{
	int y;
	int x;
	int i;

	y = 0;
	x = 0;
	i = get_line[0][0].lenght_line;
	while(get_line[y])
	{
		i = get_line[0][0].lenght_line;
		ft_putendl("Hello");
		while(i != 0)
		{
			ft_putendl("hello");
			mlx_pixel_put(point.mlx, point.win, get_line[y][x].x * 50 + 100, get_line[y][x].y * 50 +100, 0xFF0000);
			x++;
			i--;
		}
		y++;
	}
}

void	window(t_get **get_line)
{
	t_e		point;
	point.mlx = mlx_init();
	point.win = mlx_new_window(point.mlx, 1000, 1000, "42");
	mlx_key_hook(point.win, key_hook, &point);
	make_point(get_line, point);
	mlx_loop(point.mlx);
	
/*
**  mlx_loop(point.mlx);
**  pour linstant loop en commantaire
*/

}

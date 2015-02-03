/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 10:38:16 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/03 10:40:28 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	window(void)
{
	t_e		point;

	point.mlx = mlx_init();
	point.win = mlx_new_window(point.mlx, 1000, 1000, "42");
	mlx_key_hook(point.win, key_hook, &point);
	put_point(50, 50, point);
	mlx_loop(point.mlx);
/*
**  mlx_loop(point.mlx);
**  pour linstant loop en commantaire
*/

}

void	put_point(double x, double y, t_e point)
{
	mlx_pixel_put(point.mlx, point.win, x, y, 0xFF0000);
}

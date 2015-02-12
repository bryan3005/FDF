/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 10:41:59 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/12 14:45:15 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

t_e		init_window(char **argv, t_e point, int *fd)
{
	*fd = open(argv[1], O_RDWR);
	if (ft_atoi(argv[2]) >= 100 && ft_atoi(argv[2]) <= 3000)
		point.win_x = ft_atoi(argv[2]);
	else if (ft_atoi(argv[2]) < 100)
		point.win_x = 100;
	else if (ft_atoi(argv[2]) > 3000)
		point.win_x = 3000;
	if (ft_atoi(argv[3]) >= 100 && ft_atoi(argv[3]) <= 3000)
		point.win_y = ft_atoi(argv[3]);
	else if (ft_atoi(argv[3]) < 100)
		point.win_y = 100;
	else if (ft_atoi(argv[3]) > 3000)
		point.win_y = 3000;
	return(point);
}

t_e		check_primary_error(int argc, char **argv, int *fd, t_e point)
{
	if (argc == 2)
	{
		*fd = open(argv[1], O_RDWR);
		point.win_x = 1000;
		point.win_y = 1000;
	}
	else if (argc == 4)
		point = init_window(argv, point, fd);
	else
	{
		ft_putendl("usage : ./fdf file or ./fdf file win_x win_y");
		exit(EXIT_FAILURE);
	}
	if (*fd == -1)
	{
		perror("fdf ");
		exit(EXIT_FAILURE);
	}
	return(point);
}

int		check_for_empty_line(char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		while(str[i] && ft_isdigit(str[i]) != 0)
			i++;
		if (str[i] && ft_isdigit(str[i]) == 0)
			ret++;
		while(str[i] && ft_isdigit(str[i]) == 0)
			i++;
	}
	return (ret);
}

int 	check_for_bad_caracter(char *line)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while(line[i])
	{
		if (ft_isdigit(line[i]) == 0 && line[i] != ' ' && line[i] != '	' && line[i] != '-')
			ret++;
		i++;
	}
	return (ret);
}

void	draw_y(t_get p1, t_get p2, t_e e)
{
	double	a;
	double	b;
	double	dx;
	double	dy;
	double	ret;
	double	t;

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
			t = p1.y - b;
			ret = t / a;
		}
		else
			ret = p1.x;
		if ((p1.z > 0 || p2.z > 0)) 
			mlx_pixel_put(e.mlx, e.win, ret, p1.y, 0xff0000);
		else if (p1.z == 0 || p2.z == 0)
			mlx_pixel_put(e.mlx, e.win, ret, p1.y, 0xffffff);
		else
			mlx_pixel_put(e.mlx, e.win, ret, p1.y, 0x4595FF);
		p1.y++;
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

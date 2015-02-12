/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 11:01:33 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/12 14:45:16 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_e		initiate(t_e point)
{
	point.zoom =  point.win_x / (point.x * 1.8); // taille de la fenetre divi par le nombre de points
	point.zoom1 = 0.045;
	point.decalx = (point.win_x / 2) - point.x * 0.5 * point.zoom;
	point.decaly = (point.win_y / 2) - point.y * 0.5 * point.zoom;
	return (point);
}

t_e	put_in_tab(t_e point, char *str, int y)
{
	int		x;
	char	**line;

	line = ft_strsizesplit(str, ' ', &x);
	check_for_bad_length(x);
	point.x = x;
	point = initiate(point);
	while (x-- != 0)
	{
		point.map[y][x].z = ft_atoi(line[x]);
		point.map[y][x].y = y;
		point.map[y][x].x = x * point.zoom + point.decalx - point.zoom1 * point.zoom * point.map[y][x].z;
	}
	ft_freetabs(line);
	return (point);
}

t_get	**realloc_me(t_get **map, int length)
{
	t_get	**cpy;
	int 	i;

	i = 0;
	if (length != 0)
		cpy = map;
	map = (t_get**) malloc((length + 2) * sizeof(t_get*));
	while (i != length)
	{
		map[i] = cpy[i];
		i++;
	}
	map[i + 1] = NULL;
	if (length != 0)
		free(cpy);
	return (map);
}

t_e		takeline(int fd, t_e point)
{
	char	*line;
	int		ret;
	int 	y;

	ret = 1;
	y = 0;
	while (ret == 1)
	{
		point.map = realloc_me(point.map, y);
		ret = get_next_line(fd, &line);
		check_for_gnl_error(ret);
		point.map[y] = (t_get *)malloc(ft_strlen(line) * sizeof(t_get));
		check_for_other_error(line);
		if (check_for_empty_line(line) != 0)
		{
			point = put_in_tab(point, line, y);
			y++;
		}
		free(line);
	}
	point.y = y;
	point = put_y(point);
	return (point);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_get	**map;
	t_e		point;

	point = check_primary_error(argc, argv, &fd, point);
	point = takeline(fd, point);
	window(point);
	ft_putendl("hr");
	(void)map;
	return (0);
}

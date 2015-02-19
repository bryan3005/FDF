/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 11:01:33 by mbryan            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2015/02/19 14:02:26 by mbryan           ###   ########.fr       */
=======
/*   Updated: 2015/02/17 15:49:13 by mbryan           ###   ########.fr       */
>>>>>>> 55d6eee1fa7c56db3ba43af5171b721b8a5194da
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_e		initiate(t_e point)
{
	printf("e.x:%d\n", point.x);
	printf("e.y:%d\n", point.y);
	point.decala = 0;
	if (point.y >= point.x && point.valide == 1)
	{
		//printf("yyyyyy\n");
		point.zoom = point.win_y / (point.y * 1.8);
	}
	else
	{
		//printf("xxxxxxx\n");
		point.zoom = point.win_x / (point.x * 1.8);
	}

	point.zoom1 = 0.045;
	point.decalx = (point.win_x / 2) - point.x * 0.5 * point.zoom;
	point.decaly = (point.win_y / 2) - point.y * 0.5 * point.zoom;
	point.angle1 = (sin(point.decala * M_PI / 180));
	point.angle2 = (cos(point.decala * M_PI / 180));
	return (point);
}

t_e		put_in_tab(t_e point, char *str, int y)
{
	int		x;
	char	**line;

	line = ft_strsizesplit(str, ' ', &x);
	check_for_bad_length(x);
	point.x = x;
	point.valide = 0;
	point = initiate(point);
	while (x-- != 0)
	{
		point.map[y][x].z = ft_atoi(line[x]);
		point.map[y][x].y = y;
		point.map[y][x].x = x * point.zoom + point.decalx - point.zoom1 *
		point.zoom * point.map[y][x].z;
	}
	ft_freetabs(line);
	return (point);
}

t_get	**realloc_me(t_get **map, int length)
{
	t_get	**cpy;
	int		i;

	i = 0;
	if (length != 0)
		cpy = map;
	map = (t_get**)malloc((length + 2) * sizeof(t_get*));
	if (map == NULL)
		exit(EXIT_FAILURE);
	while (i != length)
	{
		map[i] = cpy[i];
		i++;
	}
	map[i + 1] = NULL;
	if (length != 0 && cpy != NULL)
		free(cpy);
	return (map);
}

t_e		takeline(int fd, t_e point)
{
	char	*line;
	int		ret;
	int		y;

	ret = 1;
	y = 0;
	while (ret == 1)
	{
		point.map = realloc_me(point.map, y);
		ret = get_next_line(fd, &line);
		check_for_gnl_error(ret);
		point.map[y] = (t_get *)malloc(ft_strlen(line) * sizeof(t_get));
		if (point.map[y] == NULL)
			exit(EXIT_FAILURE);
		check_for_other_error(line);
		if (ft_strcmp(line, "") != 0)
		{
			point = put_in_tab(point, line, y);
			y++;
		}
		free(line);
	}
	point = put_y(point, y);
	return (point);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_e		point;

	point = check_primary_error(argc, argv, &fd, point);
	point = takeline(fd, point);
	window(point);
	return (0);
}

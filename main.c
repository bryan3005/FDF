/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 11:01:33 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/09 17:07:21 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_e		initiate(t_e point)
{
	point.zoom =  point.win_x / (point.x * 1.2); // taille de la fenetre divi par le nombre de points
	point.zoom1 = 0.045;
	point.decalx = (point.win_x / 2) - point.x * 0.5 * point.zoom;
	point.decaly = 30;
	return (point);
}

t_e	put_in_tab(t_e point, char *str, int y)
{
	int		x;
	char	**line;
	static int		nbcount;
	static	int 	stat = 0;

	line = ft_strsizesplit(str, ' ', &x);
	if (stat == 0)
	{
		nbcount = x;
		stat++;
	}
	if (nbcount != x)
	{
		ft_putendl("bad length");
		exit(EXIT_FAILURE);
	}
	point.x = x;
	point = initiate(point);
	while (x-- != 0)
	{
		point.map[y][x].z = ft_atoi(line[x]);
		point.map[y][x].y = y * point.zoom + point.decaly - point.zoom1 * point.zoom * point.map[y][x].z;
		point.map[y][x].x = x * point.zoom + point.decalx - point.zoom1 * point.zoom * point.map[y][x].z;
	}
	ft_freetabs(line);
	return (point);
}

void 	check_for_other_error(char *line)
{
	if (check_for_bad_caracter(line) != 0)
	{
		ft_putendl("bad character in maps");
		exit(EXIT_FAILURE);
	}
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
	//point.map = (t_get**)malloc(1000 * sizeof(t_get*));
	y = 0;
	while (ret == 1)
	{
		point.map = realloc_me(point.map, y);
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			perror("get_next_line");
			exit(EXIT_FAILURE);
		}
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

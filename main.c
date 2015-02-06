/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 11:01:33 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/06 13:49:33 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_e	put_in_tab(t_e point, char *str, int y)
{
	int		x;
	char	**line;
	static int		nbcount;
	static	int 	stat = 0;

	point.zoom = 20;
	point.zoom1 = 0.05;
	point.decalx = 500;
	point.decaly = 500;
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

t_e		takeline(int fd, t_e point)
{
	char	*line;
	int		ret;
	int 	y;

	ret = 1;
	point.map = (t_get**)malloc(1000 * sizeof(t_get));
	y = 0;
	while (ret == 1)
	{
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

	check_primary_error(argc, argv, &fd);
	point = takeline(fd, point);
	window(point);
	ft_putendl("hr");
	(void)map;
	return (0);
}

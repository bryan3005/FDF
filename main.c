/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 11:01:33 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/03 14:11:01 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
int		key_hook(int keycode, t_e *e)
{
	(void)e;
	ft_putstr("Key :");
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 65307)
		exit(0);
	return (0);
}

void	check_primary_error(int argc, char **argv, int *fd)
{
	if (argc == 2)
		*fd = open(argv[1], O_RDWR);
	else
	{
		ft_putendl("usage : ./fdf file");
		exit(EXIT_FAILURE);
	}
	if (*fd == -1)
	{
		perror("fdf ");
		exit(EXIT_FAILURE);
	}
}

t_e	put_in_tab(t_e point, char *str, int y)
{
	int		x;
	char	**line;

	line = ft_strsizesplit(str, ' ', &x);
	point.x = x;
	while (x-- != 0)
	{
		point.map[y][x].z = ft_atoi(line[x]);
		point.map[y][x].y = y;
		point.map[y][x].x = x;
	}
	ft_freetabs(line);
	return (point);
}

t_e		takeline(int fd, t_e point)
{
	char	*line;
	int		ret;
	int 	y;

	ret = 1;
	point.map = (t_get**)malloc(100 * sizeof(t_get));
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
		point = put_in_tab(point, line, y);
		y++;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 11:01:33 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/03 12:00:56 by mbryan           ###   ########.fr       */
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

t_get	**put_in_tab(t_get **get_line, char *str, int y)
{
	int		x;
	char	**line;

	line = ft_strsizesplit(str, ' ', &x);
	get_line[0][0].lenght_line = x;
	while (x-- != 0)
	{
		get_line[y][x].z = ft_atoi(line[x]);
		get_line[y][x].y = y;
		get_line[y][x].x = x;
		printf("(%d ; %d ; %d) || ", get_line[y][x].x, get_line[y][x].y, get_line[y][x].z);
	}
	printf("lenght_line: %d\n", get_line[0][0].lenght_line  );
	ft_freetabs(line);
	return (get_line);
}

t_get	**takeline(int fd)
{
	char	*line;
	int		ret;
	t_get	**get_line;
	int 	y;

	ret = 1;
	get_line = (t_get**)malloc(100 * sizeof(t_get));
	y = 0;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			perror("get_next_line");
			exit(EXIT_FAILURE);
		}
		get_line[y] = (t_get *)malloc(ft_strlen(line) * sizeof(t_get));
		get_line = put_in_tab(get_line, line, y);
		y++;
		printf("\n");
		free(line);
	}
	return (get_line);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_get	**get_line;

	check_primary_error(argc, argv, &fd);
	get_line = takeline(fd);
	window(get_line);
	return (0);
}

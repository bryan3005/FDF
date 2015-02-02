/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 11:01:33 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/02 15:13:10 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int 	key_hook(int keycode, t_e *e)
{
	(void)e;
	ft_putstr("Key :");
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 65307)
		exit(0);
	return (0);
}

void	window(void)
{
	t_e     point;

	point.mlx = mlx_init();
	point.win = mlx_new_window(point.mlx, 1000, 1000, "42");
	mlx_key_hook(point.win, key_hook, &point);
	//mlx_loop(point.mlx);

	/// pour linstant loop en commantaire
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

void	takeline(int fd)
{
	char 	*str;
	int 	ret;
	
	str = NULL;
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &str);
		if (ret == -1)
		{
			perror("get_next_line");
			exit(EXIT_FAILURE);
		}
		ft_putendl(str);
	}

}

int main(int argc, char  **argv)
{
	int		fd;

	check_primary_error(argc, argv, &fd);
	
	takeline(fd);
	window();
	return (0);
}

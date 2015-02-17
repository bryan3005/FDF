/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 10:41:59 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/17 15:49:18 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	return (point);
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
	return (point);
}

int		check_for_empty_line(char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		while (str[i] && ft_isdigit(str[i]) != 0)
			i++;
		if (str[i] && ft_isdigit(str[i]) == 0)
			ret++;
		while (str[i] && ft_isdigit(str[i]) == 0)
			i++;
	}
	return (ret);
}

int		check_for_bad_caracter(char *line)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0 && line[i] != ' ' && line[i] != '-')
			ret++;
		i++;
	}
	return (ret);
}

void	check_for_other_error(char *line)
{
	if (check_for_bad_caracter(line) != 0)
	{
		ft_putendl("bad character in maps");
		exit(EXIT_FAILURE);
	}
}

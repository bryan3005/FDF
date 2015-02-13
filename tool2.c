/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 14:27:11 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/13 09:07:51 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_for_bad_length(int x)
{
	static int		nbcount = 0;
	static	int 	stat = 0;

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
}

void 	check_for_other_error(char *line)
{
	if (check_for_bad_caracter(line) != 0)
	{
		ft_putendl("bad character in maps");
		exit(EXIT_FAILURE);
	}
}

t_e		put_y(t_e point, int y)
{
	int i;
	int j;

	point.y = y;
	i = point.y;
	point = initiate(point);
	while(i-- != 0)
	{
		j = point.x;
		while (j-- != 0)
			point.map[i][j].y = point.map[i][j].y * point.zoom + point.decaly - point.zoom1 * point.zoom * point.map[i][j].z;
	}
	return (point);
}

void	check_for_gnl_error(int ret)
{
	if (ret == -1)
		{
			ft_putendl("Error : get_next_line");
			exit(EXIT_FAILURE);
		}
}
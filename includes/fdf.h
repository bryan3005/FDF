/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:59:30 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/03 10:42:31 by mbryan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>

typedef	struct		s_e
{
	void			*mlx;
	void			*win;
}					t_e;

typedef  struct  	s_get 
{
	int 			x;
	int 			y;
	int 			z;
}					t_get;

void				put_point(double x, double y, t_e point);
void				window(void);
int					key_hook(int keycode, t_e *e);
void				check_primary_error(int argc, char **argv, int *fd);
void				takeline(int fd);


#endif

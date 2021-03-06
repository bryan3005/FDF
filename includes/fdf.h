/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbryan <mbryan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:59:30 by mbryan            #+#    #+#             */
/*   Updated: 2015/02/15 23:56:58 by mbryan           ###   ########.fr       */
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

typedef struct		s_get
{
	int				x;
	int				y;
	int				z;
}					t_get;

typedef	struct		s_e
{
	void			*mlx;
	void			*win;
	t_get			**map;
	int				x;
	int				y;
	double			zoom;
	double			zoom1;
	double			decalx;
	double			decaly;
	double			angle1;
	double			angle2;
	int				decala;
	int				win_x;
	int				win_y;
}					t_e;

void				put_point(double x, double y, t_e point);
void				window(t_e	point);
int					key_hook(int keycode, t_e *e);
t_e					check_primary_error(int ac, char **av, int *fd, t_e point);
t_e					takeline(int fd, t_e point);
void				make_point(t_e point);
t_e					put_in_tab(t_e point, char *str, int y);
int					check_for_empty_line(char *str);
int					check_for_bad_caracter(char *line);
void				coeff_dir(t_e e);
t_e					initiate(t_e point);
void				check_for_bad_length(int x);
void				check_for_other_error(char *line);
t_e					put_y(t_e point, int y);
void				check_for_gnl_error(int ret);
void				keycode1(int keycode, t_e *e);
t_e					zoom(t_e e);
int					key_hook(int key, t_e *e);
void				draw(t_e e);
void				draw_line(t_e e, t_get p1, t_get p2);
int					is_in_map(t_e e, int x, int y);

#endif

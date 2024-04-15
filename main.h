/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:07:28 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/04/15 23:30:58 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define PI 3.14159265358979323846
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
typedef enum e_geom_type
{
	spherical,
	planar
}	t_geom_type;

typedef struct s_data_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}		t_data_img;

typedef struct s_data_vars
{
	void	*connect;
	void	*window;
}		t_data_vars;

typedef struct s_pixel
{
	double	x;
	double	y;
	double	z;
}		t_pixel;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}		t_vector;

typedef struct s_obj
{
	t_geom_type	type;
	t_pixel	centre;
	double	ray;
	t_pixel	normal;
	int		color;
}		t_obj;

void	draw_img(t_data_img *img, double width, double height, t_obj *sphere);
void	put_pixel(t_data_img *p, int x, int y, int color);
#endif
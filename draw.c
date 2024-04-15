/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:01:17 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/04/16 00:00:45 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static double	deg_to_rad(double deg)
{
	double	ret;

	ret = (deg * PI / 180.0);
	return (ret);
}

// static void	chose_solution(double t1, double t2, t_data_img *img)
// {
// 	if (t1 > t2)
// 	{
// 		p
// 	}
// }

static int	color_planar(double solut, t_pixel *pix, t_obj *obj)
{
	t_pixel	point;

	point.x = solut * pix->x;
	point.y = solut * pix->y;
	point.z = solut * pix->z;
	if (obj->color == 0)
	{
		if (fmod(point.x, 2) < 0.6 && fmod(point.x, 2) > -0.6)
			return (0);
		if (fmod(point.z, 2) < 0.6 && fmod(point.z, 2) > -0.6)
			return (0);
		return (0xb1786c);
	}
	return (obj->color);
}

static int	color_sphere(double sol, t_pixel *pix, t_obj *sphere)
{
	t_pixel	point;

	point.x = sol * pix->x;
	point.y = sol * pix->y;
	point.z = sol * pix->z;
	if ((point.y > sphere->centre.y) && (point.x >= sphere->centre.x))
		return (0x00FF00);
	if ((point.y > sphere->centre.y) && (point.x < sphere->centre.x))
		return (0xFF0000);
	if ((point.y < sphere->centre.y) && (point.x < sphere->centre.x))
		return (0xFFFF00);
	return (0x0000FF);
}

static int	color(double sol, t_pixel *pix, t_obj *sphere)
{
	if (sphere->type == spherical)
		return (color_sphere(sol, pix, sphere));
	if (sphere->type == planar)
		return (color_planar(sol, pix, sphere));
	return (0);
}

static double	check_collision(t_pixel *pix, t_obj *sphere)
{
	t_pixel		Q;
	double		delta;
	double		a;
	double		b;
	double		c;
	double		sol1;
	double		sol2;


	Q.x = -sphere->centre.x;
	Q.y = -sphere->centre.y;
	Q.z = -sphere->centre.z;
	a = pix->x * pix->x + pix->y * pix->y + pix->z * pix->z;
	b = 2 * (pix->x * Q.x + pix->y * Q.y + pix->z * Q.z);
	c = Q.x * Q.x + Q.y * Q.y + Q.z * Q.z - sphere->ray * sphere->ray;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		printf("no hit\n");
	else if (delta >= 0)
	{
		if (-b < 0)
			sol1 = (0.5 * (-b - sqrt(delta)));
		else
			sol1 = (0.5 * (-b + sqrt(delta)));
		sol2 = c / sol1;
		sol1 /= a;
		if (sol1 > 0)
		{
			if (sol2 > 0 && sol1 > sol2)
				sol1 = sol2;
			return (sol1);
		}
		if (sol2 > 0)
			return (sol2);
	}
	return (1000000000);
}

static double	check_plane(t_pixel *pix, t_obj *plane)
{
	double	ret;

	if (pix->x * plane->normal.x + pix->y * plane->normal.y + pix->z * plane->normal.z == 0)
		return (1000000000);
	ret = (plane->centre.x * plane->normal.x + plane->centre.y * plane->normal.y + plane->centre.z * plane->normal.z)
			/ (pix->x * plane->normal.x + pix->y * plane->normal.y + pix->z * plane->normal.z);
	if (ret <= 0)
		return (1000000000);
	return (ret);
}

static double	check_fonction(t_pixel *pix, t_obj *sphere)
{
	if (sphere->type == spherical)
		return (check_collision(pix, sphere));
	if (sphere->type == planar)
		return (check_plane(pix, sphere));
	return (1000000000);
}

static int	neg(int i)
{
	if (i % 2)
		return (-1);
	return (1);
}

static void	generate_sphere(t_obj *sphere, t_obj *plane)
{
	int	i;

	i = 0;
	srand(time(0));
	while (i < 10)
	{
		sphere[i].type = spherical;
		sphere[i].centre.x = (rand() % 10) * neg(i);
		sphere[i].centre.y = (rand() % 10) * neg(i);
		sphere[i].centre.z = 2 * (i + 1);
		sphere[i].ray = 2;
		i++;
	}
	sphere[0].type = planar;
	sphere[0].centre.x = plane->centre.x;
	sphere[0].centre.y = plane->centre.y;
	sphere[0].centre.z = plane->centre.z;
	sphere[0].normal.x = plane->normal.x;
	sphere[0].normal.y = plane->normal.y;
	sphere[0].normal.z = plane->normal.z;
	sphere[0].ray = 0;
	sphere[0].color = 0;
	sphere[1].type = planar;
	sphere[1].centre.x = plane->centre.x;
	sphere[1].centre.y = -plane->centre.y;
	sphere[1].centre.z = plane->centre.z;
	sphere[1].normal.x = plane->normal.x;
	sphere[1].normal.y = -plane->normal.y;
	sphere[1].normal.z = plane->normal.z;
	sphere[1].ray = 0;
	sphere[1].color = 0x3232C8;
}

static void	init_plane(t_obj *plane)
{
	plane->centre.x = 0;
	plane->centre.y = -2;
	plane->centre.z = 0;
	plane->normal.x = 0;
	plane->normal.y = 2;
	plane->normal.z = 0;
}

void	draw_img(t_data_img *img, double width, double height, t_obj *sphere)
{
	int			i;
	int			i_temp;
	double		dist;
	double		temp_dist;
	int			x;
	int			y;
	double		image_ratio;
	double		fov;
	t_pixel		pix;
	t_obj		plane;

	init_plane(&plane);
	x = 0;
	i = 0;
	pix.z = 1;
	image_ratio = width / height;
	fov = deg_to_rad(120.0);
	(void)img;
	generate_sphere(sphere, &plane);
	while (x < width)
	{
		y = 0;
		pix.x = (2.0 * x / width - 1.0) * tan(fov / 2.0) * image_ratio;
		while (y < height)
		{
			i = 0;
			dist = 1000000000;
			i_temp = 0;
			pix.y = (1.0 - 2.0 * y / height) * tan(fov / 2.0);
			while (i < 10)
			{
				temp_dist = check_fonction(&pix, sphere + i);
				if (temp_dist != 1000000000.0 && temp_dist < dist)
				{
					dist = temp_dist;
					i_temp = i;
				}
				i++;
			}
			if (dist != 1000000000)
				put_pixel(img, x, y, color(dist, &pix, sphere + i_temp));
			y++;
		}
		x++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:03:36 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/04 01:34:57 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	resize_sphere(int key, t_all *data)
{
	t_sphere	*sphere;
	t_sphere	temp;

	sphere = (t_sphere *)data->variable->all_obj[data->select];
	temp = *sphere;
	if (key == XK_KP_Add && sphere->diameter < 200)
	{
		temp.diameter += 0.2;
		if (!temp.obj.hit_box(&data->variable->cam->centre, &temp.obj))
			sphere->diameter += 0.2;
	}
	if (key == XK_KP_Subtract && sphere->diameter > 0.2)
	{
		temp.diameter -= 0.2;
		if (!temp.obj.hit_box(&data->variable->cam->centre, &temp.obj))
			sphere->diameter -= 0.2;
	}
}

void	rotation_sphere(int key, t_all *data)
{
	(void)key;
	(void)data;
}

int	collision_sphere(t_ray *ray, t_obj *to_cast)
{
	t_sphere	*sphere;
	t_vector	l;
	t_point		hit_p;
	t_point		length;

	sphere = (t_sphere *)to_cast;
	minus_vector(&l, &sphere->obj.centre, &ray->origin);
	length.x = sqrt(l.x * l.x + l.y * l.y + l.z * l.z);
	if (length.x < sphere->diameter * 0.5)
	{
		ray->length = -1;
		return (0);
	}
	length.y = dot_product(&l, &ray->dir);
	if (length.y < 0)
		return (0);
	length.z = sqrt(length.x * length.x - length.y * length.y);
	if (length.z > sphere->diameter * 0.5)
		return (0);
	ray->length = length.y - sqrt(sphere->diameter * 0.5
			* sphere->diameter * 0.5 - length.z * length.z);
	hit_p = hit(ray);
	minus_vector(&ray->normal, &hit_p, &sphere->obj.centre);
	return (1);
}

int	hit_box_sphere(t_vector *cam_pos, t_obj *obj)
{
	t_sphere	sphere;
	t_vector	z;
	t_vector	temp;
	t_vector	vertex[8];

	sphere = *(t_sphere *)obj;
	cross_product(&z, &sphere.normal, &sphere.right);
	normalize(&z);
	scalar_time_vect(&sphere.right, sphere.diameter / 2, &sphere.right);
	scalar_time_vect(&z, sphere.diameter / 2, &z);
	scalar_time_vect(&temp, sphere.diameter / 2, &sphere.normal);
	plus_vector(&temp, &sphere.obj.centre, &temp);
	plus_vector(&vertex[0], &temp, &sphere.right);
	plus_vector(&vertex[1], &temp, &z);
	minus_vector(&vertex[2], &temp, &sphere.right);
	minus_vector(&vertex[3], &temp, &z);
	scalar_time_vect(&temp, sphere.diameter / 2, &sphere.normal);
	minus_vector(&temp, &sphere.obj.centre, &temp);
	plus_vector(&vertex[4], &temp, &sphere.right);
	plus_vector(&vertex[5], &temp, &z);
	minus_vector(&vertex[6], &temp, &sphere.right);
	minus_vector(&vertex[7], &temp, &z);
	if (cam_hit_object(max_vertex(&vertex[0]), min_vertex(&vertex[0]), cam_pos))
		return (1);
	return (0);
}

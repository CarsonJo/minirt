/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:59:19 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/04 01:38:38 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	shortest_ray(float a, float b, t_ray *ray)
{
	if (a != 0 && b != 0)
	{
		if (a < b)
			ray->length = a;
		else
			ray->length = b;
		return (2);
	}
	else if (a == 0 && b == 0)
		return (0);
	else if (a == 0)
		ray->length = b;
	else
		ray->length = a;
	return (2);
}

int	hit_box_cyl(t_vector *cam_pos, t_obj *obj)
{
	t_cylinder	cyl;
	t_vector	z;
	t_vector	temp;
	t_vector	vertex[8];

	cyl = *(t_cylinder *)obj;
	cross_product(&z, &cyl.normal, &cyl.right);
	normalize(&z);
	scalar_time_vect(&temp, cyl.height / 2, &cyl.normal);
	scalar_time_vect(&z, cyl.diameter / 2, &z);
	scalar_time_vect(&cyl.right, cyl.diameter / 2, &cyl.right);
	plus_vector(&temp, &cyl.obj.centre, &temp);
	plus_vector(&vertex[0], &temp, &cyl.right);
	plus_vector(&vertex[1], &temp, &z);
	minus_vector(&vertex[2], &temp, &cyl.right);
	minus_vector(&vertex[3], &temp, &z);
	scalar_time_vect(&temp, cyl.height / 2, &cyl.normal);
	minus_vector(&temp, &cyl.obj.centre, &temp);
	plus_vector(&vertex[4], &temp, &cyl.right);
	plus_vector(&vertex[5], &temp, &z);
	minus_vector(&vertex[6], &temp, &cyl.right);
	minus_vector(&vertex[7], &temp, &z);
	if (cam_hit_object(max_vertex(&vertex[0]), min_vertex(&vertex[0]), cam_pos))
		return (1);
	return (0);
}

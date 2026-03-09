/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:14:19 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/06/23 19:37:02 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	plus_vector(t_vector *result, t_vector *a, t_vector *b)
{
	result->w = a->w;
	result->x = a->x + b->x;
	result->y = a->y + b->y;
	result->z = a->z + b->z;
}

t_vector	new_vector(float x, float y, float z)
{
	t_vector	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vector	hit(t_ray *ray)
{
	t_vector	ret;

	ret.x = ray->origin.x + ray->length * ray->dir.x;
	ret.y = ray->origin.y + ray->length * ray->dir.y;
	ret.z = ray->origin.z + ray->length * ray->dir.z;
	return (ret);
}

float	quadratic_equation(float a, float b, float c)
{
	float	delta;
	float	ret1;
	float	ret2;

	delta = b * b - 4 * a * c;
	if (delta == 0)
		return (-b / (2 * a));
	ret1 = (-b - sqrt(delta)) / (2 * a);
	ret2 = (-b + sqrt(delta)) / (2 * a);
	if (ret1 < 0 && ret2 < 0)
		return (ret1);
	else if (ret1 < 0)
		return (ret2);
	else if (ret2 < 0)
		return (ret1);
	else if (ret1 < ret2)
		return (ret1);
	return (ret2);
}

void	scalar_time_vect(t_vector *v, float scalar, t_vector *u)
{
	v->x = u->x * scalar;
	v->y = u->y * scalar;
	v->z = u->z * scalar;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:10:44 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/06/01 19:20:11 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	minus_vector(t_point *result, t_point *a, t_point *b)
{
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
}

void	vector_time_vector(t_vector *result, t_vector *a, t_vector *b)
{
	result->x = a->x * b->x;
	result->y = a->y * b->y;
	result->z = a->z * b->z;
	result->w = a->w * b->w;
}

static void	multiply_quat(t_vector *result, t_vector *u, t_vector *v)
{
	result->w = u->w * v->w - u->x * v->x - u->y * v->y - u->z * v->z;
	result->x = u->w * v->x + u->x * v->w - u->y * v->z + u->z * v->y;
	result->y = u->w * v->y + u->x * v->z + u->y * v->w - u->z * v->x;
	result->z = u->w * v->z - u->x * v->y + u->y * v->x + u->z * v->w;
}

void	rotation_inv_quaternion(t_vector *result, t_vector *quaternion
			, t_vector *u)
{
	t_vector	inv_quat;
	t_vector	temp_vect;
	t_vector	ret;

	if (!quaternion->x && !quaternion->y && !quaternion->z)
	{
		result->w = 0;
		result->x = u->x;
		result->y = u->y;
		result->z = u->z;
		return ;
	}
	temp_vect.w = 0;
	temp_vect.x = u->x;
	temp_vect.y = u->y;
	temp_vect.z = u->z;
	inv_quat.w = quaternion->w;
	inv_quat.x = -quaternion->x;
	inv_quat.y = -quaternion->y;
	inv_quat.z = -quaternion->z;
	multiply_quat(&ret, &temp_vect, &inv_quat);
	multiply_quat(result, quaternion, &ret);
}

void	rotation_quaternion(t_vector *result, t_vector *quaternion
			, t_vector *u)
{
	t_vector	inv_quat;
	t_vector	temp_vect;
	t_vector	ret;

	if (!quaternion->x && !quaternion->y && !quaternion->z)
	{
		result->w = 0;
		result->x = u->x;
		result->y = u->y;
		result->z = u->z;
		return ;
	}
	temp_vect.w = 0;
	temp_vect.x = u->x;
	temp_vect.y = u->y;
	temp_vect.z = u->z;
	inv_quat.w = quaternion->w;
	inv_quat.x = -quaternion->x;
	inv_quat.y = -quaternion->y;
	inv_quat.z = -quaternion->z;
	multiply_quat(&ret, &inv_quat, &temp_vect);
	multiply_quat(result, &ret, quaternion);
}

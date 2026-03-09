/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cylinder_mat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:04:39 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/06/21 20:31:06 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	normalize_quat(t_vector *q)
{
	float	length;

	length = q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z;
	length = sqrt(length);
	if (length == 0)
		return ;
	q->w /= length;
	q->x /= length;
	q->y /= length;
	q->z /= length;
}

int	make_cylinder_matrix(t_cylinder *cyl)
{
	t_vector	z;
	t_vector	a;
	float		dot;

	z.w = 0;
	z.x = 0;
	z.y = 1;
	z.z = 0;
	dot = dot_product(&z, &cyl->normal);
	cross_product(&a, &z, &cyl->normal);
	cyl->quaternion.w = 1 + dot;
	cyl->quaternion.x = a.x;
	cyl->quaternion.y = a.y;
	cyl->quaternion.z = a.z;
	normalize_quat(&cyl->quaternion);
	return (0);
}

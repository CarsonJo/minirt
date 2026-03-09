/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 00:34:19 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/03 20:44:55 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	rotation_x(t_vector *vect, t_vector *right, t_vector *up, float angle)
{
	t_vector	quaternion;

	quaternion.w = cos(angle / 2);
	quaternion.x = up->x * sin(angle / 2);
	quaternion.y = up->y * sin(angle / 2);
	quaternion.z = up->z * sin(angle / 2);
	normalize_quat(&quaternion);
	rotation_quaternion(vect, &quaternion, vect);
	cross_product(right, up, vect);
	normalize(right);
	normalize(vect);
}

void	rotation_y(t_vector *vect, t_vector *right, t_vector *up, float angle)
{
	t_vector	quaternion;

	quaternion.w = cos(angle / 2);
	quaternion.x = right->x * sin(angle / 2);
	quaternion.y = right->y * sin(angle / 2);
	quaternion.z = right->z * sin(angle / 2);
	normalize_quat(&quaternion);
	rotation_quaternion(vect, &quaternion, vect);
	cross_product(up, vect, right);
	normalize(up);
	normalize(vect);
}

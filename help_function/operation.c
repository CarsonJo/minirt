/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:01:09 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/05/31 16:39:32 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	cross_product(t_vector *w, t_vector *u, t_vector *v)
{
	w->x = u->y * v->z - u->z * v->y;
	w->y = u->z * v->x - u->x * v->z;
	w->z = u->x * v->y - u->y * v->x;
	w->w = 0;
}

float	dot_product(t_vector *u, t_vector *v)
{
	float	ret;

	ret = u->x * v->x + u->y * v->y + u->z * v->z;
	return (ret);
}

void	normalize(t_vector *u)
{
	float	a;

	a = u->x * u->x + u->y * u->y + u->z * u->z;
	if (a == 0)
		return ;
	a = sqrt(a);
	u->x /= a;
	u->y /= a;
	u->z /= a;
}

t_vector	vector_time_matrix(t_vector *u, float *v)
{
	t_vector	ret;

	ret.x = u->x * v[0] + u->y * v[4] + u->z * v[8] + u->w * v[12];
	ret.y = u->x * v[1] + u->y * v[5] + u->z * v[9] + u->w * v[13];
	ret.z = u->x * v[2] + u->y * v[6] + u->z * v[10] + u->w * v[14];
	ret.w = u->x * v[3] + u->y * v[7] + u->z * v[11] + u->w * v[15];
	return (ret);
}

float	vect_len(t_vector *vect)
{
	return (sqrt(vect->x * vect->x + vect->y * vect->y + vect->z * vect->z));
}

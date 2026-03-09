/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:40:14 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/04 01:35:17 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_vector	max_vertex(t_vector *arr)
{
	int		i;
	float	x;
	float	y;
	float	z;

	i = 1;
	x = arr->x;
	y = arr->y;
	z = arr->z;
	while (i < 8)
	{
		if (arr[i].x > x)
			x = arr[i].x;
		if (arr[i].y > y)
			y = arr[i].y;
		if (arr[i].z > z)
			z = arr[i].z;
		i++;
	}
	return ((t_vector){x + 0.5, y + 0.5, z + 0.5, 0});
}

t_vector	min_vertex(t_vector *arr)
{
	int		i;
	float	x;
	float	y;
	float	z;

	i = 1;
	x = arr->x;
	y = arr->y;
	z = arr->z;
	while (i < 8)
	{
		if (arr[i].x < x)
			x = arr[i].x;
		if (arr[i].y < y)
			y = arr[i].y;
		if (arr[i].z < z)
			z = arr[i].z;
		i++;
	}
	return ((t_vector){x - 0.5, y - 0.5, z - 0.5, 0});
}

int	cam_hit_object(t_vector max, t_vector min, t_vector *cam)
{
	if (cam->x >= min.x && cam->x <= max.x && cam->y >= min.y && cam->y <= max.y
		&& cam->z >= min.z && cam->z <= max.z)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:03:23 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/06/25 00:36:18 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	resize_plane(int key, t_all *data)
{
	(void)key;
	(void)data;
}

void	rotation_plane(int key, t_all *data)
{
	t_plane		*plan;
	t_vector	up;

	plan = (t_plane *)data->variable->all_obj[data->select];
	cross_product(&up, &plan->normal, &plan->right);
	if (key == XK_a || key == XK_A)
		rotation_x(&plan->normal, &plan->right, &up, 0.174533);
	else if (key == XK_D || key == XK_d)
		rotation_x(&plan->normal, &plan->right, &up, -0.174533);
	else if (key == XK_W || key == XK_w)
		rotation_y(&plan->normal, &plan->right, &up, 0.174533);
	else if (key == XK_S || key == XK_s)
		rotation_y(&plan->normal, &plan->right, &up, -0.174533);
}

int	check_disk(t_ray *temp, t_plane *disk, float r)
{
	t_point		point;
	t_vector	vector;

	if (!collision_plane(temp, (t_obj *)disk))
		return (0);
	point.x = temp->dir.x * temp->length;
	point.y = temp->dir.y * temp->length;
	point.z = temp->dir.z * temp->length;
	vector.x = disk->obj.centre.x - point.x;
	vector.y = disk->obj.centre.y - point.y;
	vector.z = disk->obj.centre.z - point.z;
	if (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z > r * r)
		return (0);
	return (1);
}

void	create_plane(t_plane *new, t_cylinder *old)
{
	new->normal.w = 0;
	new->normal.x = 0;
	new->normal.y = 1;
	new->normal.z = 0;
	new->obj.centre = old->obj.centre;
	new->obj.centre.y -= old->height / 2;
}

int	collision_plane(t_ray *ray, t_obj *to_cast)
{
	t_plane	*plane;

	plane = (t_plane *)to_cast;
	if (ray->dir.x * plane->normal.x + ray->dir.y * plane->normal.y
		+ ray->dir.z * plane->normal.z == 0)
		return (0);
	ray->length = ((plane->obj.centre.x - ray->origin.x) * plane->normal.x
			+ (plane->obj.centre.y - ray->origin.y) * plane->normal.y
			+ (plane->obj.centre.z - ray->origin.z) * plane->normal.z)
		/ (ray->dir.x * plane->normal.x + ray->dir.y * plane->normal.y
			+ ray->dir.z * plane->normal.z);
	if (ray->length < 0)
		return (0);
	if (dot_product(&plane->normal, &ray->dir) < 0)
		ray->normal = plane->normal;
	else
		ray->normal = (t_vector){.w = 1, .x = -plane->normal.x,
			.y = -plane->normal.y, .z = -plane->normal.z};
	return (1);
}

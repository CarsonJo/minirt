/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:01:11 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/06/24 23:41:37 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	resize_cylinder(int key, t_all *data)
{
	t_cylinder	*cyl;
	t_cylinder	temp;

	temp = *(t_cylinder *)data->variable->all_obj[data->select];
	cyl = (t_cylinder *)data->variable->all_obj[data->select];
	if (key == XK_KP_Add && cyl->diameter < 200)
	{
		temp.diameter += 0.2;
		if (!temp.obj.hit_box(&data->variable->cam->centre, &temp.obj))
			cyl->diameter += 0.2;
	}
	if (key == XK_KP_Subtract && cyl->diameter > 0.2)
		cyl->diameter -= 0.2;
	if (key == XK_KP_Right && cyl->height > 0.2)
		cyl->height -= 0.2;
	if (key == XK_KP_Prior && cyl->height < 1000)
	{
		temp.height += 0.2;
		if (!temp.obj.hit_box(&data->variable->cam->centre, &temp.obj))
			cyl->height += 0.2;
	}
}

void	cylinder_rotation(int key, t_all *data)
{
	t_cylinder	*cyl;
	t_cylinder	temp;
	t_vector	last;

	cyl = (t_cylinder *)data->variable->all_obj[data->select];
	temp = *cyl;
	cross_product(&last, &cyl->normal, &cyl->right);
	if (key == XK_a || key == XK_A)
		rotation_y(&temp.normal, &temp.right, &last, 0.174533);
	else if (key == XK_D || key == XK_d)
		rotation_y(&temp.normal, &temp.right, &last, -0.174533);
	else if (key == XK_W || key == XK_w)
		rotation_x(&temp.normal, &temp.right, &last, 0.174533);
	else if (key == XK_S || key == XK_s)
		rotation_x(&temp.normal, &temp.right, &last, -0.174533);
	if (!temp.obj.hit_box(&data->variable->cam->centre, &temp.obj))
	{
		cyl->right = temp.right;
		cyl->normal = temp.normal;
	}
	make_cylinder_matrix(cyl);
}

static int	finite_cylinder(float t, t_ray *ray
				, t_ray *temp_ray, t_cylinder *cyl)
{
	t_plane	first;
	float	t1;
	float	t2;

	t1 = 0;
	t2 = 0;
	temp_ray->origin = (t_point){.x = 0, .y = 0, .z = 0, .w = 0};
	create_plane(&first, cyl);
	if (check_disk(temp_ray, &first, cyl->diameter / 2))
		t1 = temp_ray->length;
	first.obj.centre.y += cyl->height;
	if (check_disk(temp_ray, &first, cyl->diameter / 2))
		t2 = temp_ray->length;
	if (t * temp_ray->dir.y < cyl->obj.centre.y + cyl->height / 2
		&& t * temp_ray->dir.y > cyl->obj.centre.y - cyl->height / 2
		&& (!t1 || t < t1) && (!t2 || t < t2))
	{
		ray->length = t;
		return (1);
	}
	return (shortest_ray(t1, t2, ray));
}

int	hit_normal(t_ray *ray, t_ray *temp, t_cylinder *fake, float flag)
{
	t_point	hit_p;

	if (flag == 0)
		return (0);
	temp->length = ray->length;
	temp->origin = (t_point){0, 0, 0, 0};
	hit_p = hit(temp);
	if (flag == 2)
	{
		if (hit_p.y > fake->obj.centre.y)
			ray->normal = (t_vector){.x = 0, .y = 1, .z = 0};
		else
			ray->normal = (t_vector){.x = 0, .y = -1, .z = 0};
	}
	else
	{
		minus_vector(&ray->normal, &hit_p, &(fake->obj.centre));
		ray->normal.y = 0;
	}
	return (1);
}

int	collision_cylinder(t_ray *ray, t_obj *to_cast)
{
	t_cylinder	*cyl;
	t_cylinder	f;
	t_point		var;
	t_ray		temp;

	cyl = (t_cylinder *)to_cast;
	f = *cyl;
	temp = *ray;
	minus_vector(&f.obj.centre, &f.obj.centre, &ray->origin);
	rotation_inv_quaternion(&temp.dir, &cyl->quaternion, &ray->dir);
	rotation_inv_quaternion(&f.obj.centre, &cyl->quaternion, &f.obj.centre);
	var.x = temp.dir.x * temp.dir.x + temp.dir.z * temp.dir.z;
	var.y = 2 * (-f.obj.centre.x * temp.dir.x + -f.obj.centre.z * temp.dir.z);
	var.z = (-f.obj.centre.x * -f.obj.centre.x + -f.obj.centre.z
			* -f.obj.centre.z - cyl->diameter * 0.5 * cyl->diameter * 0.5);
	if (var.y * var.y - 4 * var.x * var.z < 0)
		return (0);
	if (hit_normal(ray, &temp, &f, finite_cylinder
			(quadratic_equation(var.x, var.y, var.z), ray, &temp, &f)))
	{
		rotation_quaternion(&ray->normal, &cyl->quaternion, &ray->normal);
		return (1);
	}
	return (0);
}

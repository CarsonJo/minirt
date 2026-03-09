/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmastora <jmastora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:27:00 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/05 10:49:04 by jmastora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_chckfrr(t_point point)
{
	if (point.x == 0 && point.y == 0 && point.z == 0)
		return (true);
	return (false);
}

t_sphere	*initialize_sphere(void)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->obj.type = CYLINDER;
	sphere->cam_to_world = 0;
	return (sphere);
}

t_sphere	*populate_sphere(t_sphere *sphere, char *str, t_camera *cam)
{
	char	**l;

	l = ft_split(str, ' ');
	if (!l)
		return (free(sphere), NULL);
	sphere->obj.centre = build_point(l[1]);
	if (sphere->obj.centre.w == -2)
		return (free_tab(l), free(sphere), NULL);
	sphere->diameter = ft_atof(l[2]);
	if (sphere->diameter < 0.2 || sphere->diameter > 200)
		return (free_tab(l), free(sphere), NULL);
	sphere->obj.color = rgbtoint(l[3]);
	if (sphere->obj.color <= 0)
		return (free_tab(l), free(sphere), NULL);
	sphere->obj.collision = collision_sphere;
	sphere->obj.hit_box = hit_box_sphere;
	sphere->obj.resize = resize_sphere;
	sphere->obj.rotation = rotation_sphere;
	sphere->normal = cam->orientation_vector;
	sphere->right = cam->right;
	free_tab(l);
	return (sphere);
}

t_sphere	*build_sp(char *str, t_camera *cam)
{
	t_sphere	*sphere;

	sphere = initialize_sphere();
	if (!sphere)
		return (NULL);
	sphere = populate_sphere(sphere, str, cam);
	if (!sphere)
		return (NULL);
	return (sphere);
}

t_plane	*build_pl(char *str, t_camera *cam)
{
	t_plane	*plane;
	char	**l;

	plane = initialize_plane();
	if (!plane)
		return (NULL);
	l = ft_split(str, ' ');
	if (!l)
		return (NULL);
	plane->obj.centre = build_point(l[1]);
	if (plane->obj.centre.w == -2)
		return (free_tab(l), free(plane), NULL);
	plane->normal = build_point(l[2]);
	if (plane->normal.w == -2 || ft_chckfrr(plane->normal))
		return (free_tab(l), free(plane), NULL);
	plane->obj.color = rgbtoint(l[3]);
	if (plane->obj.color <= 0)
		return (free_tab(l), free(plane), NULL);
	plane->obj.collision = collision_plane;
	plane->obj.hit_box = hit_box_plane;
	plane->obj.resize = resize_plane;
	plane->obj.rotation = rotation_plane;
	calcul_plane(plane, cam);
	free_tab(l);
	return (plane);
}

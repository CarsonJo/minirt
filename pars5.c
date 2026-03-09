/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:25:58 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/04 18:44:53 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_light	*build_light(char *str)
{
	t_light	*light;
	char	**l;
	int		i;

	i = 0;
	light = malloc(sizeof (t_light));
	if (!light)
		return (NULL);
	l = ft_split(str, ' ');
	if (!l)
		return (NULL);
	light->centre = build_point(l[1]);
	if (light->centre.w == -2)
		return (free_tab(l), NULL);
	light->brightness = ft_atof(l[2]);
	if (light->brightness > 1.0 || light->brightness < 0)
		return (free_tab(l), NULL);
	light->color = rgbtoint(l[3]);
	if (light->color < 0)
		return (free_tab(l), NULL);
	free_tab(l);
	return (light);
}

void	calcul_cam(t_camera *cam)
{
	t_vector	z;
	t_vector	y;
	t_vector	x;

	z = cam->orientation_vector;
	if (z.x == 1 && z.y == 0 && z.z == 0)
		y = (t_vector){.x = 0, .y = 1, .z = 0};
	else if (z.x == -1 && z.y == 0 && z.z == 0)
		y = (t_vector){.x = 0, .y = 1, .z = 0};
	else if (z.z > 0)
		cross_product(&y, &z, &(t_vector){.x = 1, .y = 0, .z = 0});
	else
		cross_product(&y, &(t_vector){.x = 1, .y = 0, .z = 0}, &z);
	if (z.z > 0)
		cross_product(&x, &y, &z);
	else
		cross_product(&x, &z, &y);
	cam->up = y;
	cam->right = x;
	normalize(&cam->orientation_vector);
}

t_camera	*build_camera(char *str)
{
	t_camera	*camera;
	char		**l;
	int			i;

	i = 0;
	camera = malloc(sizeof (t_camera));
	if (!camera)
		return (NULL);
	l = ft_split(str, ' ');
	if (!l)
		return (NULL);
	camera->centre = build_point(l[1]);
	if (camera->centre.w == -2)
		return (free_tab(l), NULL);
	camera->orientation_vector = build_point(l[2]);
	if (camera->orientation_vector.w == -2
		|| ft_chckfrr(camera->orientation_vector))
		return (free_tab(l), NULL);
	camera->fov = ft_atof(l[3]);
	if (camera->fov <= 0 && camera->fov >= 180)
		return (free_tab(l), NULL);
	camera->fov *= PI / 180;
	calcul_cam(camera);
	free_tab(l);
	return (camera);
}

void	calcul_plane(t_plane *plane, t_camera *cam)
{
	t_vector	z;
	t_vector	y;

	z = plane->normal;
	if (z.x == 1 && z.y == 0 && z.z == 0)
		y = (t_vector){.x = 0, .y = 0, .z = -1};
	else if (z.x == -1 && z.y == 0 && z.z == 0)
		y = (t_vector){.x = 0, .y = 0, .z = 1};
	else if (z.z > 0)
		cross_product(&y, &z, &(t_vector){.x = 1, .y = 0, .z = 0});
	else
		cross_product(&y, &(t_vector){.x = 1, .y = 0, .z = 0}, &z);
	plane->right = y;
	plane->obj.rot_x = cam->right;
	plane->obj.rot_y = cam->up;
}

t_plane	*initialize_plane(void)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->obj.type = PLANE;
	plane->cam_to_world = 0;
	return (plane);
}

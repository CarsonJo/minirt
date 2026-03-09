/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:36:49 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/03 23:07:20 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_collision(t_ray *ray, t_obj **obj)
{
	int		i;
	float	temp;
	int		ret;
	t_point	normal;

	ret = -1;
	temp = INFINITY;
	i = 0;
	ray->length = 0;
	while (obj[i]->type != END)
	{
		if (obj[i]->collision(ray, obj[i]) && ray->length < temp
			&& ray->length > 0.001)
		{
			ret = i;
			temp = ray->length;
			normal = ray->normal;
		}
		i++;
	}
	ray->length = temp;
	ray->normal = normal;
	return (ret);
}

int	norm(t_ray *ray, t_all *data, float *len)
{
	float	dot;

	ray->origin.x = ray->origin.x + ray->length * ray->dir.x;
	ray->origin.y = ray->origin.y + ray->length * ray->dir.y;
	ray->origin.z = ray->origin.z + ray->length * ray->dir.z;
	minus_vector(&ray->dir, &data->variable->light->centre, &ray->origin);
	*len = vect_len(&ray->dir);
	normalize(&ray->dir);
	normalize(&ray->normal);
	dot = dot_product(&ray->dir, &ray->normal);
	if (dot <= 0)
		return (1);
	return (0);
}

static void	see_light(t_ray *ray, t_all *data, t_ray *view_dir, t_norm *var)
{
	float	specular;
	float	brightness;
	float	dot;

	specular = 0;
	brightness = data->variable->ambiant->brightness;
	dot = dot_product(&ray->dir, &ray->normal);
	if ((check_collision(ray, data->variable->all_obj) < 0
			|| ray->length > var->len) && fabs(ray->length - var->len) > 0.01)
	{
		brightness += data->variable->light->brightness * dot;
		if (data->variable->all_obj[var->index]->type != PLANE)
			specular = specular_light(ray, view_dir);
	}
	pixel_put(data, var->pix->a, var->pix->b, color_brightness(
			data->variable->light->color,
			data->variable->all_obj[var->index]->color, brightness, specular));
}

//faire le dot product avec un objet derriere donne de la
//transparence a utiliser peut etre;
int	color_pixel(t_vector *coord_pixel, t_all *data, t_pair *pix)
{
	int			index;
	float		brightness;
	float		len;
	t_ray		ray;
	t_ray		view_dir;

	brightness = data->variable->ambiant->brightness;
	ray.origin = data->variable->cam->centre;
	ray.dir = *coord_pixel;
	normalize(&ray.dir);
	index = check_collision(&ray, data->variable->all_obj);
	if (index < 0 || ray.length < 0)
		return (pixel_put(data, pix->a, pix->b, 0x000000));
	view_dir = ray;
	if (norm(&ray, data, &len))
		return (pixel_put(data, pix->a, pix->b, color_brightness(
					data->variable->light->color,
					data->variable->all_obj[index]->color, brightness, 0)));
	see_light(&ray, data, &view_dir, &(t_norm){index, len, pix});
	return (0);
}

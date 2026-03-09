/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bright_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:07:44 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/03 22:03:36 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	color_brightness(int light_color, int color, float brightness
				, float specular)
{
	int	ret;
	int	red;
	int	green;
	int	blue;

	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	red = red * brightness * ((light_color >> 16) & 0xFF) / 255
		+ specular * ((light_color >> 16) & 0xFF);
	green = green * brightness * ((light_color >> 8) & 0xFF) / 255
		+ specular * ((light_color >> 8) & 0xFF);
	blue = blue * brightness * (light_color & 0xFF) / 255
		+ specular * ((light_color >> 0) & 0xFF);
	red = min(red, 255);
	blue = min(blue, 255);
	green = min(green, 255);
	ret = (red << 16) + (green << 8) + blue;
	return (ret);
}

float	specular_light(t_ray *light_dir, t_ray *view_dir)
{
	t_vector	reflect;
	float		dot;
	float		ret;

	light_dir->dir.x *= -1;
	light_dir->dir.y *= -1;
	light_dir->dir.z *= -1;
	view_dir->dir.x *= -1;
	view_dir->dir.y *= -1;
	view_dir->dir.z *= -1;
	dot = dot_product(&light_dir->dir, &view_dir->normal);
	reflect.x = light_dir->dir.x - 2 * dot * view_dir->normal.x;
	reflect.y = light_dir->dir.y - 2 * dot * view_dir->normal.y;
	reflect.z = light_dir->dir.z - 2 * dot * view_dir->normal.z;
	normalize(&reflect);
	ret = pow(fmax(dot_product(&reflect, &view_dir->dir), 0.0), 32);
	return (ret * 0.5);
}

int	pixel_put(t_all *p, int x, int y, int color)
{
	char	*dest;

	dest = p->img->data + (y * p->img->size_line + x * (p->img->bpp / 8));
	if (p->img->endian)
	{
		dest[0] = (color >> 24) & 0xFF;
		dest[1] = (color >> 16) & 0xFF;
		dest[2] = (color >> 8) & 0xFF;
		dest[3] = color & 0xFF;
	}
	if (!p->img->endian)
	{
		dest[0] = color & 0xFF;
		dest[1] = color >> 8 & 0xFF;
		dest[2] = color >> 16 & 0xFF;
		dest[3] = color >> 24 & 0xFF;
	}
	return (0);
}

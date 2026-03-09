/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:55:37 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/03 23:07:53 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	to_world_coord(t_vector *coord, t_all *data)
{
	*coord = vector_time_matrix(coord, &(data->variable->cam->cam_to_world[0]));
	return (0);
}

int	draw(t_all *data, t_pair *screen)
{
	float		image_ratio;
	t_vector	coord_pixel;
	t_pair		index;
	float		x;

	coord_pixel.w = 0;
	index.a = 0;
	image_ratio = (float)screen->a / (float)screen->b;
	while (index.a < screen->a)
	{
		x = (2 * ((float)index.a + 0.5) / screen->a - 1.0)
			* data->variable->cam->fov * image_ratio;
		index.b = -1;
		while (++index.b < screen->b)
		{
			coord_pixel.x = x;
			coord_pixel.y = (1 - 2 * (index.b + 0.5) / screen->b)
				* data->variable->cam->fov;
			coord_pixel.z = 1;
			to_world_coord(&coord_pixel, data);
			color_pixel(&coord_pixel, data, &index);
		}
		index.a++;
	}
	return (0);
}

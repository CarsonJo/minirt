/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_click.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:40 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/02 20:50:17 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	handle_click(int click, int x, int y, void *data)
{
	t_all		*temp;
	t_ray		ray;
	t_vector	pixel;
	float		image_ratio;

	temp = (t_all *)data;
	image_ratio = (float)temp->screen_size.a / (float)temp->screen_size.b;
	if (click != Button1)
	{
		temp->select = -1;
		return (0);
	}
	pixel.x = (2 * ((float)x + 0.5) / temp->screen_size.a - 1.0)
		* temp->variable->cam->fov * image_ratio;
	pixel.y = (1 - 2 * (y + 0.5) / temp->screen_size.b)
		* temp->variable->cam->fov;
	pixel.z = 1;
	pixel.w = 0;
	to_world_coord(&pixel, temp);
	ray.dir = pixel;
	ray.origin = temp->variable->cam->centre;
	normalize(&ray.dir);
	temp->select = check_collision(&ray, temp->variable->all_obj);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:57:12 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/06/24 01:52:25 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	obj_translation(int key, t_all *data)
{
	t_vector	*centre;
	t_vector	*cam_c;

	cam_c = &data->variable->cam->centre;
	centre = &data->variable->all_obj[data->select]->centre;
	if (key == XK_Left && check_object(data->variable->all_obj
			, cam_c, &data->variable->cam->right, plus_vector))
		minus_vector(centre, centre, &data->variable->cam->right);
	else if (key == XK_Right && check_object(data->variable->all_obj
			, cam_c, &data->variable->cam->right, minus_vector))
		plus_vector(centre, centre, &data->variable->cam->right);
	else if (key == XK_Up && check_object(data->variable->all_obj
			, cam_c, &data->variable->cam->orientation_vector, plus_vector))
		plus_vector(centre, centre, &data->variable->cam->up);
	else if (key == XK_Down && check_object(data->variable->all_obj
			, cam_c, &data->variable->cam->orientation_vector, minus_vector))
		minus_vector(centre, centre, &data->variable->cam->up);
}

void	object_movement(int key, t_all *data)
{
	if (key == XK_Left || key == XK_Right || key == XK_Down
		|| key == XK_Up)
		obj_translation(key, data);
	else if (key == XK_a || key == XK_A || key == XK_w || key == XK_W
		|| key == XK_d || key == XK_D || key == XK_s || key == XK_S)
		data->variable->all_obj[data->select]->rotation(key, data);
	else if (key == XK_KP_Add || key == XK_KP_Subtract || key == XK_KP_Right
		|| key == XK_KP_Prior)
		data->variable->all_obj[data->select]->resize(key, data);
}

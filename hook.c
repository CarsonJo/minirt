/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:32:25 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/12 18:47:52 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_object(t_obj **obj, t_vector *u, t_vector *v,
					void (*op)(t_vector *, t_vector *, t_vector *))
{
	t_vector	final_pos;
	int			i;

	i = 0;
	op(&final_pos, u, v);
	while (obj[i]->type != END)
	{
		if (obj[i]->hit_box(&final_pos, obj[i]))
			return (0);
		i++;
	}
	return (1);
}

//flemme mais pas envoyer centre a check object peut etre
//dangereux si check_object modifie centre ou alors preciser const dans check
static void	player_move(int key, t_all *all)
{
	t_vector	*centre;
	t_vector	*normal;
	t_vector	right;

	normal = &all->variable->cam->orientation_vector;
	centre = &all->variable->cam->centre;
	if (normal->x == 0 && normal->y == 1 && normal->z == 0)
		right = (t_vector){.x = 1, .y = 0, .z = 0};
	else
		cross_product(&right, normal, &(t_vector){.x = 0, .y = 1, .z = 0});
	normalize(&right);
	if (key == XK_Right
		&& check_object(all->variable->all_obj, centre, &right, minus_vector))
		minus_vector(centre, centre, &right);
	else if (key == XK_Up
		&& check_object(all->variable->all_obj, centre, normal, plus_vector))
		plus_vector(centre, centre, normal);
	else if (key == XK_Left
		&& check_object(all->variable->all_obj, centre, &right, plus_vector))
		plus_vector(centre, centre, &right);
	else if (key == XK_Down
		&& check_object(all->variable->all_obj, centre, normal, minus_vector))
		minus_vector(centre, centre, normal);
}

static void	camera_rotation(int key, t_all *all)
{
	t_vector	*up;
	t_vector	*right;

	up = &all->variable->cam->up;
	right = &all->variable->cam->right;
	if (key == XK_a || key == XK_A)
		rotation_x(&all->variable->cam->orientation_vector,
			right, up, -0.174533);
	else if (key == XK_w || key == XK_W)
		rotation_y(&all->variable->cam->orientation_vector,
			right, up, -0.174533);
	else if (key == XK_s || key == XK_S)
		rotation_y(&all->variable->cam->orientation_vector,
			right, up, 0.174533);
	else if (key == XK_d || key == XK_D)
		rotation_x(&all->variable->cam->orientation_vector,
			right, up, 0.174533);
	normalize(&all->variable->cam->orientation_vector);
	make_cam_to_world(all->variable->cam);
}

int	handle_key_press(int key, void *data)
{
	t_all	*all;

	all = (t_all *)data;
	if (key == XK_Escape)
	{
		quit_struct(all);
		mlx_loop_end(all->id->connect);
		return (0);
	}
	else if (all->select >= 0)
		object_movement(key, all);
	else if (key == XK_Left || key == XK_Right || key == XK_Down
		|| key == XK_Up)
		player_move(key, all);
	else if (key == XK_a || key == XK_A || key == XK_w || key == XK_W
		|| key == XK_d || key == XK_D || key == XK_s || key == XK_S)
		camera_rotation(key, all);
	draw(all, &all->screen_size);
	mlx_put_image_to_window(all->id->connect, all->id->window, all->img->img,
		0, 0);
	return (0);
}

int	handle_cross(void *data)
{
	return (handle_key_press(XK_Escape, data));
}

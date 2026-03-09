/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cam_to_world.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:44:43 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/06/23 15:45:55 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

//generate an orthogonal vector of z and fill it in x
void	generate_orthogonal_vector(t_vector *y, t_vector *z)
{
	int	i;

	i = 0;
	if (!z->y)
		y->y = 1;
	else if (!z->x)
		y->x = 1;
	else if (!z->z)
		y->z = 1;
	else
	{
		y->x = 1;
		y->y = 1;
		y->z = (-z->x - z->y) / z->z ;
	}
	normalize(y);
}

//generate two vector orthogonal to z
void	generate_cartesian_coordinate(t_vector *x, t_vector *y, t_vector *z)
{
	t_vector	*test;

	test = &(t_vector){.x = 0, .y = 1, .z = 0};
	if (z->x == 0 && z->y == 1 && z->z == 0)
	{
		x->x = 1;
		x->y = 0;
		x->z = 0;
	}
	else
		cross_product(x, test, z);
	normalize(x);
	cross_product(y, z, x);
	normalize(x);
}

static void	fill_row(float *arr, t_vector *vect)
{
	arr[0] = vect->x;
	arr[1] = vect->y;
	arr[2] = vect->z;
	arr[3] = vect->w;
}

//nom a changer
void	nawaknojutsu(t_vector *test, float *mat, t_vector *x, t_vector *y)
{
	int			count;

	count = 0;
	if (test->x < 0)
		count++;
	if (test->y < 0)
		count++;
	if (test->z < 0)
		count++;
	if (count <= 1)
		return ;
	fill_row(mat, y);
	fill_row(mat + 4, x);
}

int	make_cam_to_world(t_camera *cam)
{
	t_vector	x;
	t_vector	y;
	t_vector	test;

	test.w = 0;
	test.x = -1;
	test.y = 1;
	test.w = 1;
	ft_bzero(cam->cam_to_world, 16 * sizeof(float));
	ft_bzero(&x, sizeof(t_vector));
	ft_bzero(&y, sizeof(t_vector));
	generate_cartesian_coordinate(&x, &y, &cam->orientation_vector);
	fill_row(cam->cam_to_world, &x);
	fill_row(cam->cam_to_world + 4, &y);
	fill_row(cam->cam_to_world + 8, &cam->orientation_vector);
	fill_row(cam->cam_to_world + 12, &cam->centre);
	return (0);
}

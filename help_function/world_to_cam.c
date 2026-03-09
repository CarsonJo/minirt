/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_to_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:10:53 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/05/27 10:13:37 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	neg(int a)
{
	if (a % 2)
		return (-1);
	return (1);
}

int	invert_matrix(float *to_invert, float *ret)
{
	float	determinant;
	float	temp_mat[9];
	float	adjugate_mat[16];
	int		i;

	if (ret == 0)
	{
		ret = malloc(sizeof(float) * 16);
		if (!ret)
			return (1);
	}
	i = -1;
	determinant = matrix_determinant4(to_invert);
	if (determinant == 0)
		return (1);
	while (++i < 16)
		adjugate_mat[i] = neg(i / 4 + 1 + i % 4 + 1) * matrix_determinant3(
				fill_mat3(&(temp_mat[0]), to_invert, i / 4 + 1, i % 4 + 1));
	i = -1;
	while (++i < 16)
		ret[i] = adjugate_mat[i] / determinant;
	return (0);
}

int	make_world_to_cam(t_camera *cam)
{
	invert_matrix(&(cam->cam_to_world[0]), &(cam->world_to_cam[0]));
	return (0);
}

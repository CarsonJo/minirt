/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:36:36 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/06/23 15:45:32 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	fill_index(int del_, int *fill)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (k++ < 4)
	{
		if (k == del_)
			continue ;
		fill[j] = k - 1;
		j++;
	}
}

float	*fill_mat3(float *m, float *m4, int del_a, int del_b)
{
	int	i[4];
	int	j[4];
	int	u;

	u = 0;
	fill_index(del_a, &(i[0]));
	fill_index(del_b, &(j[0]));
	while (u < 9)
	{
		m[u] = m4[i[u / 3] * 4 + j[u % 3]];
		u++;
	}
	return (m);
}

float	matrix_determinant3(float *m)
{
	float	det;

	det = m[0] * m[4] * m[8] + m[1] * m[5] * m[6] + m[2] * m[3] * m[7]
		- m[2] * m[4] * m[6] - m[1] * m[3] * m[8] - m[0] * m[5] * m[7];
	return (det);
}

float	matrix_determinant4(float *mat)
{
	float	det;
	float	mat1[9];
	float	mat2[9];
	float	mat3[9];
	float	mat4[9];

	det = mat[4 * 0] * matrix_determinant3(fill_mat3(&(mat1[0]), mat, 1, 1))
		- mat[4 * 1] * matrix_determinant3(fill_mat3(&(mat2[0]), mat, 2, 1))
		+ mat[4 * 2] * matrix_determinant3(fill_mat3(&(mat3[0]), mat, 3, 1))
		- mat[4 * 3] * matrix_determinant3(fill_mat3(&(mat4[0]), mat, 4, 1));
	return (det);
}

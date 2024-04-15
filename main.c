/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:11:34 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/04/16 00:02:03 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_pixel(t_data_img *p, int x, int y, int color)
{
	char	*dest;

	dest = p->data + (y * p->size_line + x * (p->bpp / 8));
	if (!p->endian)
	{
		dest[0] = (color >> 24) & 0xFF;
		dest[1] = (color >> 16) & 0xFF;
		dest[2] = (color >> 8) & 0xFF;
		dest[3] = color & 0xFF;
	}
	if (p->endian)
	{
		dest[0] = color & 0xFF;
		dest[1] = color >> 8 & 0xFF;
		dest[2] = color >> 16 & 0xFF;
		dest[3] = color >> 24 & 0xFF;
	}
}

int	main(void)
{
	t_data_img	img;
	t_data_vars	id;
	t_obj		sphere[10];
	int			a, b;

	id.connect = mlx_init();
	mlx_get_screen_size(id.connect, &a, &b);
	id.window = mlx_new_window(id.connect, a, b, "my_window");
	img.img = mlx_new_image(id.connect, a, b);
	img.data = mlx_get_data_addr(img.img, &img.bpp, &img.size_line,
		&img.endian);
	if (a > 0 && b > 0)
		draw_img(&img, (double)a, (double)b, &sphere[0]);
	mlx_put_image_to_window(id.connect, id.window, img.img, 0, 0);
	mlx_loop(id.connect);
	mlx_destroy_image(id.connect, img.img);
	mlx_destroy_window(id.connect, id.window);
	mlx_destroy_display(id.connect);
	return (0);
}

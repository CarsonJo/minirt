/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:20:27 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/12 18:46:07 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	init_screen(t_mlx_id *id, t_pair *pair, t_data_img *image,
	t_all *to_pass)
{
	id->connect = mlx_init();
	if (!id->connect)
		return (0);
	mlx_get_screen_size(id->connect, &pair->a, &pair->b);
	id->window = mlx_new_window(id->connect, pair->a, pair->b, "title");
	if (!id->window)
		return (0);
	image->img = mlx_new_image(id->connect, pair->a, pair->b);
	if (!image->img)
		return (0);
	image->data = mlx_get_data_addr(image->img, &image->bpp, &image->size_line,
			&image->endian);
	to_pass->id = id;
	to_pass->img = image;
	return (0);
}

static int	loop(t_mlx_id *id, t_all *data)
{
	mlx_hook(id->window, DestroyNotify, 0, handle_cross, data);
	mlx_hook(id->window, KeyRelease, KeyReleaseMask, handle_key_press, data);
	mlx_hook(id->window, ButtonPress, ButtonPressMask, handle_click, data);
	mlx_put_image_to_window(id->connect, id->window, data->img->img, 0, 0);
	mlx_loop(id->connect);
	quit_serveur(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_all_data	data;
	t_mlx_id	id;
	t_pair		screen_size;
	t_data_img	image;
	t_all		to_pass;

	ft_bzero(&image, sizeof(t_data_img));
	ft_bzero(&data, sizeof(t_all_data));
	ft_bzero(&id, sizeof(t_mlx_id));
	ft_bzero(&to_pass, sizeof(t_all));
	if (argc != 2)
		return (write(2, "./minirt files.rt\n", 19));
	if (!argv[1] || !*argv[1])
		return (write(2, "empty arguments\n", 17));
	parsing(&data, argv[1], &to_pass);
	if (make_cam_to_world(to_pass.variable->cam))
		return (quit_struct(&to_pass));
	if (init_screen(&id, &screen_size, &image, &to_pass))
		return (quit_struct(&to_pass), quit_serveur(&to_pass));
	to_pass.screen_size = screen_size;
	draw(&to_pass, &screen_size);
	loop(&id, &to_pass);
	return (0);
}

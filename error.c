/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:24:25 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/04 20:34:40 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_tab(char **to_free)
{
	int	i;

	i = 0;
	if (to_free)
	{
		while (to_free[i])
		{
			free(to_free[i]);
			i++;
		}
		free(to_free);
	}
}

static void	free_obj(t_obj **all_obj)
{
	int	i;

	i = 0;
	while (all_obj[i] && all_obj[i]->type != END)
	{
		free(all_obj[i]);
		i++;
	}
	if (all_obj[i])
		free(all_obj[i]);
	free(all_obj);
}

int	quit_struct(void *data)
{
	t_all	*my_data;

	my_data = (t_all *)data;
	if (my_data->variable->all_obj)
		free_obj(my_data->variable->all_obj);
	if (my_data->variable->ambiant)
		free(my_data->variable->ambiant);
	if (my_data->variable->cam)
		free(my_data->variable->cam);
	if (my_data->variable->light)
		free(my_data->variable->light);
	return (1);
}

int	quit_serveur(void *data)
{
	t_all	*my_data;

	my_data = (t_all *)data;
	if (my_data->img->img)
		mlx_destroy_image(my_data->id->connect, my_data->img->img);
	if (my_data->id->window)
		mlx_destroy_window(my_data->id->connect, my_data->id->window);
	if (my_data->id->connect)
	{
		mlx_destroy_display(my_data->id->connect);
		free(my_data->id->connect);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmastora <jmastora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:21:32 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/05 10:41:34 by jmastora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	build_ambient_data(t_all_data *data, char *line)
{
	static int	i = 0;

	if (i)
		return (false);
	i = 1;
	data->ambiant = build_amb(line);
	if (data->ambiant == NULL)
		return (false);
	return (true);
}

bool	build_camera_data(t_all_data *data, char *line)
{
	static int	i = 0;

	if (i)
		return (false);
	i = 1;
	data->cam = build_camera(line);
	if (data->cam == NULL)
		return (false);
	return (true);
}

bool	build_light_data(t_all_data *data, char *line)
{
	static int	i = 0;

	if (i)
		return (false);
	i = 1;
	data->light = build_light(line);
	if (!data->light)
		return (false);
	return (true);
}

bool	build_sphere_data(t_all_data *data, char *line, int *j)
{
	data->all_obj[*j] = (t_obj *)build_sp(line, data->cam);
	if (data->all_obj[*j] == NULL)
		return (false);
	(*j)++;
	return (true);
}

bool	build_plane_data(t_all_data *data, char *line, int *j)
{
	data->all_obj[*j] = (t_obj *)build_pl(line, data->cam);
	if (data->all_obj[*j] == NULL)
		return (false);
	(*j)++;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:21:25 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/04 18:54:51 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	build_cylinder_data(t_all_data *data, char *line, int *j)
{
	data->all_obj[*j] = (t_obj *)build_cy(line);
	if (data->all_obj[*j] == NULL)
		return (false);
	(*j)++;
	return (true);
}

bool	allocate_objects(t_all_data *data, char **map)
{
	data->all_obj = malloc(sizeof(t_obj *) * (ft_nbofform(map) + 1));
	ft_bzero(data->all_obj, sizeof(t_obj *) * (ft_nbofform(map) + 1));
	if (!data->all_obj)
		return (false);
	return (true);
}

bool	process_map_line(t_all_data *data, char *line, int *j)
{
	if (line[0] == 'A')
		return (build_ambient_data(data, line));
	else if (line[0] == 'C')
		return (build_camera_data(data, line));
	else if (line[0] == 'L')
		return (build_light_data(data, line));
	else if (line[0] == 's' || line[1] == 'p')
		return (build_sphere_data(data, line, j));
	else if (line[0] == 'p' || line[1] == 'l')
		return (build_plane_data(data, line, j));
	else if (line[0] == 'c' || line[1] == 'y')
		return (build_cylinder_data(data, line, j));
	return (true);
}

bool	build_struc(t_all_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!allocate_objects(data, map))
		return (false);
	while (map[i])
	{
		if (!process_map_line(data, map[i], &j))
			return (false);
		i++;
	}
	data->all_obj[ft_nbofform(map)] = malloc(sizeof(t_obj));
	if (!data->all_obj[ft_nbofform(map)])
		return (false);
	data->all_obj[ft_nbofform(map)]->type = END;
	return (true);
}

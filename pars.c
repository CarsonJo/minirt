/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmastora <jmastora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:25:36 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/05 10:37:06 by jmastora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	calcul_cyl(t_cylinder *cyl, char **l)
{
	t_vector	z;
	t_vector	y;

	z = cyl->normal;
	if (z.x == 0 && z.y == 1 && z.z == 0)
		y = (t_vector){.x = 1, .y = 0, .z = 0};
	else if (z.x == 0 && z.y == -1 && z.z == 0)
		y = (t_vector){.x = 1, .y = 0, .z = 0};
	else if (z.z > 0)
		cross_product(&y, &z, &(t_vector){.x = 1, .y = 0, .z = 0});
	else
		cross_product(&y, &(t_vector){.x = 1, .y = 0, .z = 0}, &z);
	cyl->right = y;
	normalize(&cyl->normal);
	normalize(&cyl->right);
	make_cylinder_matrix(cyl);
	free_tab(l);
}

t_cylinder	*initialize_cylinder(void)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->obj.type = CYLINDER;
	return (cylinder);
}

t_cylinder	*set_cylinder_properties(t_cylinder *cylinder, char *str)
{
	char		**l;

	l = ft_split(str, ' ');
	if (!l)
		return (NULL);
	cylinder->obj.centre = build_point(l[1]);
	cylinder->normal = build_point(l[2]);
	if ((cylinder->obj.centre.w == -2)
		|| (cylinder->normal.w == -2 || ft_chckfrr(cylinder->normal)))
		return (free_tab(l), NULL);
	cylinder->diameter = ft_atof(l[3]);
	if (cylinder->diameter < 0.2 || cylinder->diameter > 200)
		return (free_tab(l), NULL);
	cylinder->height = ft_atof(l[4]);
	if (cylinder->height <= 0.2 || cylinder->height > 1000)
		return (free_tab(l), NULL);
	cylinder->obj.color = rgbtoint(l[5]);
	if (cylinder->obj.color <= 0)
		return (free_tab(l), NULL);
	cylinder->obj.collision = collision_cylinder;
	cylinder->obj.hit_box = hit_box_cyl;
	cylinder->obj.resize = resize_cylinder;
	cylinder->obj.rotation = cylinder_rotation;
	calcul_cyl(cylinder, l);
	return (cylinder);
}

t_cylinder	*build_cy(char *str)
{
	t_cylinder	*cylinder;

	cylinder = initialize_cylinder();
	if (!cylinder)
		return (NULL);
	if (!set_cylinder_properties(cylinder, str))
	{
		free(cylinder);
		return (NULL);
	}
	return (cylinder);
}

void	parsing(t_all_data *data, char *str, t_all *to_pass)
{
	char	**map;

	if (ft_strlen(str) < 4)
		exit(write(2, "met un input correct\n", 22));
	if (!ft_dotrt(str, ".rt"))
		exit(write(2, "need .rt files\n", 16));
	map = extract(str);
	if (!map)
		exit(2);
	if (checkingvalid(map) && allineedisall(map) && build_struc(data, map))
		ft_frft(map);
	else
	{
		write(2, "ERREUR \n", 9);
		map = ft_frft(map);
		to_pass->variable = data;
		quit_struct(to_pass);
		exit(2);
	}
	to_pass->variable = data;
	to_pass->select = -1;
	out_of_object(to_pass);
	check_mandatory(to_pass);
}

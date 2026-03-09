/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:25:52 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/12 14:41:13 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	**extract(char *str)
{
	char		**splited;
	int			file;
	static char	*super_string = NULL;

	file = open(str, O_RDONLY);
	while (1 && file != -1)
	{
		str = get_next_line(file, 0);
		if (!str || str[0] == '\n')
			break ;
		super_string = ft_strjoin(super_string, str);
		free(str);
	}
	if (str && str[0] == '\n')
		free(str);
	get_next_line(file, 1);
	close(file);
	if (super_string)
	{
		splited = ft_split(super_string, '\n');
		if (!splited)
			return (free(super_string), NULL);
		return (free(super_string), splited);
	}
	return (NULL);
}

int	ft_nbofform(char **map)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		if (map[i][0] == 's' || map[i][1] == 'p')
			count++;
		if (map[i][0] == 'p' || map[i][1] == 'l')
			count++;
		if (map[i][0] == 'c' || map[i][1] == 'y')
			count++;
		i++;
	}
	return (count);
}

t_point	build_point(char *ch)
{
	t_point	point;
	char	**coords;

	coords = ft_split(ch, ',');
	if (!coords)
		return ((t_point){0, 0, 0, -2});
	point.x = ft_atof(coords[0]);
	point.y = ft_atof(coords[1]);
	point.z = ft_atof(coords[2]);
	point.w = 0.0;
	ft_frft(coords);
	return (point);
}

t_ambiant	*build_amb(char *str)
{
	t_ambiant	*amb;
	char		**a;
	int			i;

	i = 0;
	amb = malloc(sizeof (t_ambiant));
	if (!amb)
		return (NULL);
	a = ft_split(str, ' ');
	if (!a)
		return (NULL);
	amb->brightness = ft_atof(a[1]);
	amb->color = rgbtoint(a[2]);
	if (amb->color < 0)
		return (free_tab(a), NULL);
	free_tab(a);
	return (amb);
}

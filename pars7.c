/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 00:30:14 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/12 14:41:51 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	out_of_object(t_all *data)
{
	if (!check_object(data->variable->all_obj, &data->variable->cam->centre,
			&(t_vector){0, 0, 0, 0}, minus_vector))
	{
		printf("camera can not be in object please for my sanity don't break "
			"the parsing\n");
		quit_struct(data);
		exit(1);
	}
}

void	check_mandatory(t_all *data)
{
	if (!data->variable->ambiant || !data->variable->light
		|| !data->variable->cam)
	{
		printf("one necessary argument missing\n");
		quit_struct(data);
		exit(1);
	}
}

bool	ft_atoi(char *str, int *nb)
{
	int	i;
	int	pos;
	int	val;

	val = 0;
	pos = 1;
	i = 0;
	if (!str || !*str)
		return (false);
	if (str[i] == '-')
	{
		pos = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			val = val * 10 + str[i] - '0';
		else
			return (false);
		i++;
	}
	*nb = val * pos;
	return (true);
}

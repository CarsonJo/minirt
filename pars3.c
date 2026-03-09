/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:25:47 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/03 21:25:48 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	validspace(char *str)
{
	static char	*tab[6] = {"A", "C", "L", "sp", "pl", "cy"};
	int			i;
	int			valid;

	valid = 0;
	i = 0;
	if (!str)
		return (false);
	while (i < 6)
	{
		if ((tab[i][0] && str[0] && tab[i][0] == str[0])
			&& (tab[i][1] == str[1]))
			valid++;
		else if ((tab[i][0] && str[0] && tab[i][0] == str[0]))
			valid++;
		i++;
	}
	if (valid == 1)
		return (true);
	return (false);
}

bool	checkingvalid(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) < 12)
			return (false);
		if (!validspace(map[i]))
			return (false);
		while (map[i][j])
		{
			if (!validchar(map[i][j]))
				return (false);
			j++;
		}
		j = 0;
		i++;
	}
	return (true);
}

bool	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && n > i)
	{
		if (s1[i] != s2[i])
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	allineedisnorm(t_normj n)
{
	if (!n.a || !n.c || !n.l)
		return (false);
	if (!n.cy && !n.pl && !n.sp)
		return (false);
	return (true);
}

bool	allineedisall(char **map)
{
	static t_normj	normj = {0};

	while (map[normj.i])
	{
		if (map[normj.i][0] == 'A')
			normj.a = true;
		if (map[normj.i][0] == 'C')
			normj.c = true;
		if (map[normj.i][0] == 'L')
			normj.l = true;
		if (ft_strncmp(map[normj.i], "sp", 2))
			normj.sp = true;
		if (ft_strncmp(map[normj.i], "pl", 2))
			normj.pl = true;
		if (ft_strncmp(map[normj.i], "cy", 2))
			normj.cy = true;
		normj.i++;
	}
	return (allineedisnorm(normj));
}

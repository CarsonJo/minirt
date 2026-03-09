/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:37:57 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/12 14:41:37 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	advance_to_dec(char **str, int *sign, double *result)
{
	if (*(*str) == '-')
	{
		(*sign) = -1;
		(*str)++;
	}
	while (*(*str) >= '0' && *(*str) <= '9')
	{
		(*result) = (*result) * 10.0 + (*(*str) - '0');
		(*str)++;
	}
}

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		decimal_found;

	result = 0.0;
	fraction = 1.0;
	sign = 1;
	decimal_found = 0;
	advance_to_dec(&str, &sign, &result);
	if (*str == '.')
	{
		decimal_found = 1;
		str++;
		while (*str >= '0' && *str <= '9')
		{
			result = result * 10.0 + (*str - '0');
			fraction *= 10.0;
			str++;
		}
	}
	if (decimal_found)
		result /= fraction;
	return (result * sign);
}

int	rgbtoint(char *colorStr)
{
	int		r;
	int		g;
	int		b;
	char	**token;

	r = 0;
	g = 0;
	b = 0;
	token = ft_split(colorStr, ',');
	if (!token)
		return (-1);
	if (!ft_atoi(token[0], &r) || !ft_atoi(token[1], &g)
		|| !ft_atoi(token[2], &b))
	{
		write(2, "COLOR ", 7);
	}
	if (r > 255 || r < 0)
		return (free_tab(token), -1);
	if (g > 255 || g < 0)
		return (free_tab(token), -1);
	if (b > 255 || b < 0)
		return (free_tab(token), -1);
	free_tab(token);
	return ((r << 16) | (g << 8) | b);
}

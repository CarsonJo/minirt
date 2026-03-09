/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:25:42 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/09 13:39:27 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_strcmp(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (false);
		i++;
	}
	if (!str[i] && !str2[i])
		return (true);
	return (false);
}

bool	ft_dotrt(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			return (ft_strcmp(str + i, str2));
		i++;
	}
	return (false);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *str, char *str2)
{
	char	*joined;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str) + ft_strlen(str2);
	joined = malloc(sizeof(char) * (len + 1));
	i = -1;
	j = -1;
	if (str2[0] == '\n')
		return (NULL);
	if (!joined)
		return (NULL);
	if (ft_strlen(str))
		while (str[++i])
			joined[i] = str[i];
	else
		i++;
	if (ft_strlen(str2))
		while (str2[++j])
			joined[i + j] = str2[j];
	joined[i + j] = 0;
	free(str);
	return (joined);
}

bool	validchar(char c)
{
	if (c != ' ' && !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z')
		&& !(c >= '0' && c <= '9') && c != '.' && c != ',' && c != '-')
		return (false);
	return (true);
}

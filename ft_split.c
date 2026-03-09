/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmastora <jmastora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:39:46 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/03 22:51:35 by jmastora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	ft_nbw(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			word++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (word);
}

char	**ft_frft(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static char	*ft_cpy(char *split, char *s, int start, int j)
{
	int	wsize;
	int	i;

	i = 0;
	wsize = j - start;
	split = malloc(sizeof(char) * wsize + 1);
	if (!(split))
		return (NULL);
	while (i < (wsize))
	{
		split[i] = (char)s[i + start];
		i++;
	}
	split[i] = '\0';
	return (split);
}

static int	ft_init(int *i, int *j, char *s, char c)
{
	*i = -1;
	*j = 0;
	return (ft_nbw(s, c));
}

char	**ft_split(char *s, char c)
{
	char	**split;
	int		size;
	int		i;
	int		start;
	int		j;

	if (!s)
		return (0);
	size = ft_init(&i, &j, s, c);
	split = malloc(sizeof(char *) * (size + 1));
	if (!(split))
		return (NULL);
	while (s[j] && ++i < size)
	{
		while ((s[j] == c) && s[j])
			j++;
		start = j;
		while ((s[j] != c) && s[j])
			j++;
		split[i] = ft_cpy(split[i], s, start, j);
		if (!(split[i]))
			return (ft_frft(split));
	}
	split[size] = 0;
	return (split);
}

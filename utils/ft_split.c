/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:20:40 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/20 15:06:58 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int ft_wlen(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int counter(char const *s, char c)
{
	int x;
	int i;

	x = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		i = ft_wlen(s, c);
		s += i;
		if (i > 0)
			x++;
	}
	return (x);
}

char **ft_split(char const *s, char c)
{
	int parts_count;
	int count;
	int len;
	char **copy;

	parts_count = counter(s, c);
	copy = (char **)malloc((parts_count + 1) * sizeof(char *));
	if (!copy)
		return (0);
	count = -1;
	while (++count < parts_count)
	{
		while (*s && *s == c)
			s++;
		len = ft_wlen(s, c);
		copy[count] = (char *)malloc((len + 1) * sizeof(char));
		if (copy[count] == NULL)
			return (0);
		ft_strlcpy(copy[count], s, len + 1);
		s += len;
	}
	copy[parts_count] = 0;
	return (copy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:19:42 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/28 12:22:25 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_atoi(const char *str)
{
	int i;
	unsigned long long value;
	int s;

	i = 0;
	value = 0;
	s = 1;
	while ((str[i] && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			s *= -1;
		if (str[i + 1] == '-' || str[i + 1] == '+')
			s = 0;
		i++;
	}
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
		value = (value * 10) + str[i++] - '0';
	return (s * value);
}

int ft_isalpha(char *ch)
{
	int i;

	i = 0;
	while (ch[i])
	{
		if ((ch[i] >= 'a' && ch[i] <= 'z') || (ch[i] >= 'A' && ch[i] <= 'Z'))
			return (1);
		i++;
	}
	return (0);
}

int ft_isascii(char *a)
{
	int i;

	i = 0;
	while (a[i])
	{
		// if (a[i] == '-' || a[i] == '+')
		// 	i++;
		// if (a[i] == 32)
		// 	i++;
		if (!(a[i] >= 48 && a[i] <= 57))
			return (1);
		i++;
	}
	return (0);
}

int ft_strchr(const char *str, int c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

int ft_strchr1(const char *str, int c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int ft_strcmp(const char *str1, const char *str2)
{
	size_t i;
	unsigned char *s1;
	unsigned char *s2;

	i = 0;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

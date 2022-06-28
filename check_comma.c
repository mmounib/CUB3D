/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comma.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:19:55 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/27 10:49:49 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_char(char **color)
{
	int i = 0;
	while (color[i])
	{
		if (ft_isalpha(color[i]) || ft_isascii(color[i]))
			return (1);
		i++;
	}
	return (0);
}

int check_comma(t_info *infos, int j, int i)
{
	int count;
	char **color;

	count = 0;
	color = ft_split(&infos->map->map[i][j], ',');
	if (check_char(color))
	{
		printf("Invalid Color Number In Floor!!\n");
		exit(0);
	}
	infos->map->red = ft_atoi(color[0]);
	infos->map->green = ft_atoi(color[1]);
	infos->map->blue = ft_atoi(color[2]);
	if (infos->map->red > 255 || infos->map->red < 0 || infos->map->green < 0 || infos->map->green > 255 || infos->map->blue < 0 || infos->map->blue > 255)
	{
		printf("Error!! You Exceed The range [0,255]\n");
		exit(0);
	}
	while (infos->map->map[i][j])
	{
		if (infos->map->map[i][j] == ',')
			count++;
		j++;
	}
	if (count == 2)
		return (1);
	return (0);
}

int check_comma1(t_info *infos, int j, int i)
{
	int count;
	char **color;

	count = 0;
	color = ft_split(&infos->map->map[i][j], ',');
	if (check_char(color))
	{
		printf("Invalid Color Number In Ceiling!!\n");
		exit(0);
	}
	infos->map->red1 = ft_atoi(color[0]);
	infos->map->green1 = ft_atoi(color[1]);
	infos->map->blue1 = ft_atoi(color[2]);
	if (infos->map->red1 > 255 || infos->map->red1 < 0 || infos->map->green1 < 0 || infos->map->green1 > 255 || infos->map->blue1 < 0 || infos->map->blue1 > 255)
	{
		printf("Error!! You Exceeded The range [0,255]\n");
		exit(0);
	}
	while (infos->map->map[i][j])
	{
		if (infos->map->map[i][j] == ',')
			count++;
		j++;
	}
	if (count == 2)
		return (1);
	return (0);
}
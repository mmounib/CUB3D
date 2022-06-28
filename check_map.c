/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:21:59 by oouazize          #+#    #+#             */
/*   Updated: 2022/01/31 14:03:32 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void checkmap2(t_info *infos, int *i, int *count, int j)
{
	if (!ft_strncmp(infos->map->map[*i], "NO ", 3))
	{
		(*count)++;
		infos->map->no_text = ft_strdup(&infos->map->map[*i][j]);
		infos->map->north = 1;
	}
	if (!ft_strncmp(infos->map->map[*i], "SO ", 3))
	{
		(*count)++;
		infos->map->so_text = ft_strdup(&infos->map->map[*i][j]);
		infos->map->south = 1;
	}
	if (!ft_strncmp(infos->map->map[*i], "EA ", 3))
	{
		(*count)++;
		infos->map->ea_text = ft_strdup(&infos->map->map[*i][j]);
		infos->map->east = 1;
	}
	if (!ft_strncmp(infos->map->map[*i], "WE ", 3))
	{
		(*count)++;
		infos->map->we_text = ft_strdup(&infos->map->map[*i][j]);
		infos->map->west = 1;
	}
}

void checkmap3(t_info *infos, int *i, int *count, int j)
{
	if (!ft_strncmp(infos->map->map[*i], "F ", 2))
	{
		(*count)++;
		j = 2;
		ft_skipspace(infos, &j, *i);
		if (!check_comma(infos, j, *i))
		{
			printf("Error, More Than 2 Commas\n");
			exit(0);
		}
		infos->map->ceiling = 1;
	}
	if (!ft_strncmp(infos->map->map[*i], "C ", 2))
	{
		(*count)++;
		j = 2;
		ft_skipspace(infos, &j, *i);
		if (!check_comma1(infos, j, *i))
		{
			printf("Error, More Than 2 Commas!!\n");
			exit(0);
		}
		infos->map->floor = 1;
	}
}

void calc_length(t_info *infos)
{
	int		i;

	infos->map->map_length = ft_strlen(infos->map->map[0]);
	i = 1;
	while (infos->map->map[i])
	{
		if (infos->map->map_length < ft_strlen(infos->map->map[i]))
			infos->map->map_length = ft_strlen(infos->map->map[i]);
		i++;
	}
}

void checkmap1(t_info *infos, int *i)
{
	int j;
	int count = 0;
	int len;

	infos->map->map = ft_getmap(infos);
	calc_length(infos);
	while (infos->map->map[*i])
	{
		infos->map->map[*i] = ft_strtrim(infos->map->map[*i], " ");
		j = 3;
		ft_skipspace(infos, &j, *i);
		checkmap2(infos, i, &count, j);
		checkmap3(infos, i, &count, j);
		if (count == 6)
			break;
		(*i)++;
	}
}

void error_player(void)
{
	printf("Error In Map Variables!!\n");
    exit(0);
}

void    check_player2(t_info *infos, int *flag, int i, int j)
{
    if (*flag)
    {
        printf("Invalid In Map Variables\n");
        exit (0);
    }
    *flag = 1;
    infos->mathi->playerdir = infos->map->map1[i][j];
}

void check_player(t_info *infos, int flag)
{
    int i;
    int j;

    i = -1;
    while (infos->map->map1[++i])
    {
        j = -1;
        while (infos->map->map1[i][++j])
        {
            if (infos->map->map1[i][j] == 'N')
                check_player2(infos, &flag, i, j);
            else if (infos->map->map1[i][j] == 'S')
                check_player2(infos, &flag, i, j);
            else if (infos->map->map1[i][j] == 'W')
                check_player2(infos, &flag, i, j);
            else if (infos->map->map1[i][j] == 'E')
                check_player2(infos, &flag, i, j);
            else if (infos->map->map1[i][j] != 48 && infos->map->map1[i][j] != 49 && infos->map->map1[i][j] != 32)
            	error_player();
        }
    }
    if (!flag)
		error_player();
}
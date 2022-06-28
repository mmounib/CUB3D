/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:20:06 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/28 14:44:46 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_line1(t_info *info)
{
	int i;

	i = -1;
	while (info->map->map1[0][++i])
		if (info->map->map1[0][i] != '1')
			return (0);
	return (1);
}

int get_addr(t_info *data, int y, int x, int flag)
{
	char *dst;

	dst = NULL;
	x = x % 64;
	y = y % 64;
	if (flag == 4 || flag == 0)
		dst = data->addr4 + (y * data->size_l1 + x * (data->bpp1 / 8));
	else if (flag == 3)
		dst = data->addr3 + (y * data->size_l1 + x * (data->bpp1 / 8));
	else if (flag == 2)
		dst = data->addr2 + (y * data->size_l1 + x * (data->bpp1 / 8));
	else if (flag == 1)
		dst = data->addr1 + (y * data->size_l1 + x * (data->bpp1 / 8));
	return (*(unsigned int *)dst);
}

void dda(double pa, int x, t_info *infos)
{
	int y = 0;
	int color;
	float b;
	int flag = 0;
	int dx = infos->mathi->point_x - infos->mathi->pos_x;
	int dy = infos->mathi->point_y - infos->mathi->pos_y;
	int steps;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;

	float X = infos->mathi->pos_x;
	float Y = infos->mathi->pos_y;
	for (int i = 0; i <= steps; i++)
	{
		//printf("%d    %d\n", (int)round(Y) / 64, (int)round(X) / 64);
		if (!infos->map->map1[(int)round(Y) / 64][(int)round(X) / 64] || infos->map->map1[(int)round(Y) / 64][(int)round(X) / 64] == '1')
		{
			if (infos->map->map1[(int)round(Y) / 64][(int)(round(X - Xinc) / 64)] != '1')
			{
				if (Xinc > 0)
					flag = 4;
				else
					flag = 3;
			}
			else if (infos->map->map1[(int)round(Y - Yinc) / 64][(int)(round(X) / 64)] != '1')
			{
				if (Yinc > 0)
					flag = 2;
				else
					flag = 1;
			}
			double X1 = (infos->x) - ((int)round(X));
			double Y1 = (infos->y) - ((int)round(Y));
			infos->mathi->distance_plane = (WIN_WIDTH / 2) / tan(33 * PI / 180);
			infos->mathi->distance_wall = cos((pa - infos->mathi->angle) * PI / 180) * sqrt(pow(X1, 2) + pow(Y1, 2));
			infos->mathi->wall_h = 64 / (cos((pa - infos->mathi->angle) * PI / 180) * sqrt(pow(X1, 2) + pow(Y1, 2))) * fabs(infos->mathi->distance_plane);
			infos->mathi->floor1 = (WIN_HEIGHT / 2) - (infos->mathi->wall_h / 2);
			infos->mathi->wall_h = infos->mathi->floor1 + infos->mathi->wall_h;
			while (y <= infos->mathi->floor1)
			{
				my_mlx_pixel_put(infos, x, y, infos->map->rgb1);
				y++;
			}
			while (y < infos->mathi->wall_h && y < WIN_HEIGHT)
			{
				if (flag == 3 || flag == 4)
					b = fmod(Y / 64, 1);
				else
					b = fmod(X / 64, 1);
				color = get_addr(infos, ((y - (infos->mathi->floor1)) / (infos->mathi->wall_h - infos->mathi->floor1)) * 64, b * 64, flag);
				my_mlx_pixel_put(infos, x, y, color);
				y++;
			}
			while (y < WIN_HEIGHT)
			{
				my_mlx_pixel_put(infos, x, y, infos->map->rgb);
				y++;
			}
			break;
		}
			// my_mlx_pixel_put(infos, round(X), round(Y), 0xFFFF00);
		X += Xinc;
		Y += Yinc;
	}
}

char **ft_getmap(t_info *infos)
{
	char *line;
	char *temp;
	char **map;

	temp = ft_strdup("");
	line = get_next_line(infos->map->fd);
	while (line)
	{
		temp = ft_strjoin(temp, line);
		free(line);
		line = get_next_line(infos->map->fd);
	}
	map = ft_split(temp, '\n');
	free(temp);
	return (map);
}

void ft_skipspace(t_info *infos, int *j, int i)
{
	while (infos->map->map[i][*j] == 32)
		(*j)++;
}

void draw_rays(t_info *infos)
{
	double pa;
	int x;
	int d;
	double h;

	x = -1;
	pa = infos->mathi->angle - 33;
	d = WIN_WIDTH / 60;
	h = (double)1 / d;
	while (pa < infos->mathi->angle + 33 && ++x < WIN_WIDTH)
	{
		infos->mathi->pos_x = infos->x;
		infos->mathi->pos_y = infos->y;
		infos->mathi->point_x = (infos->x + (10000000 * cos(pa * PI / 180)));
		infos->mathi->point_y = (infos->y + (10000000 * sin(pa * PI / 180)));
		dda(pa, x, infos);
		pa += h;
	}
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img, 0, 0);
	// mlx_put_image_to_window(infos->mlx, infos->win, infos->play, infos->x - 17, infos->y - 17);
}

int handle_input(int keysym, t_info *infos)
{
	if (keysym == 53)
	{
		printf("Game Over\n");
		exit(0);
	}
	if (keysym == 2 || keysym == 124)
		event_right(&infos, keysym);
	else if (keysym == 0 || keysym == 123)
		event_left(&infos, keysym);
	else if (keysym == 1 || keysym == 125)
		event_down(&infos);
	else if (keysym == 13 || keysym == 126)
		event_up(&infos);
	return (0);
}

int closed(void)
{
	printf("Game Over\n");
	exit(0);
}

void intt(t_info *infos)
{
	mlx_hook(infos->win, 17, 1L << 17, &closed, infos);
	mlx_hook(infos->win, 2, 1L << 0, &handle_input, infos);
}

int main(int argc, char **argv)
{
	t_info info;
	int i;

	if (argc > 2)
		return (0);
	init(&info);
	intt(&info);
	info.map->fd = open(argv[1], O_RDONLY, 0777);
	info.i = 0;
	info.j = 0;
	info.mathi->delta_x = 5;
	info.mathi->delta_y = 0;
	info.mathi->angle = 0;
	if (info.map->fd < 0 || !ft_strstr(argv[1], ".cub"))
	{
		printf("error in the extension!!\n");
		exit(0);
	}
	i = 0;
	checkmap1(&info, &i);
	if (!info.map->south || !info.map->east || !info.map->west || !info.map->north || !info.map->ceiling || !info.map->floor)
	{
		printf("Wrong element!!\n");
		exit(0);
	}
	info.map->rgb = (info.map->red << 16) | (info.map->green << 8) | (info.map->blue << 0);
	info.map->rgb1 = (info.map->red1 << 16) | (info.map->green1 << 8) | (info.map->blue1 << 0);
	init2(&info);
	replace_map(&info, i);
	checkmap_0(&info);
	checkallmap(&info);
	check_player(&info, 0);
    if (info.mathi->playerdir == 'N')
        info.mathi->angle = -90;
    else if (info.mathi->playerdir == 'S')
        info.mathi->angle = 90;
    else if (info.mathi->playerdir == 'W')
        info.mathi->angle = 180;
    else if (info.mathi->playerdir == 'E')
        info.mathi->angle = 0;
	draw_map(&info);
	draw_player(&info);
	draw_rays(&info);
	mlx_loop(info.mlx);
}
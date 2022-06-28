/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:59:36 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/27 22:01:36 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	black_window(t_info **infos)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			my_mlx_pixel_put(*infos, j, i, 0x000000);
	}
}

void rotate_angle(t_info **infos, int side)
{
	if (side > 0)
	{
		(*infos)->mathi->angle += 10;
		if ((*infos)->mathi->angle < 0)
			(*infos)->mathi->angle += 360;
		(*infos)->mathi->delta_x = cos((*infos)->mathi->angle * PI / 180) * 10;
		(*infos)->mathi->delta_y = sin((*infos)->mathi->angle * PI / 180) * 10;
	}
	else
	{
		(*infos)->mathi->angle -= 10;
		if ((*infos)->mathi->angle > 360)
			(*infos)->mathi->angle -= 360;
		(*infos)->mathi->delta_x = cos((*infos)->mathi->angle * PI / 180) * 10;
		(*infos)->mathi->delta_y = sin((*infos)->mathi->angle * PI / 180) * 10;
	}
}

void event_right(t_info **infos, int keysym)
{
	(*infos)->flag1 = 0;
	if (keysym == 2)
	{
		if ((*infos)->flag)
			return;
		(*infos)->mathi->angle += 90;
		if ((*infos)->mathi->angle < 0)
			(*infos)->mathi->angle += 360;
		(*infos)->y += sin((*infos)->mathi->angle * PI / 180) * 10;
		(*infos)->x += cos((*infos)->mathi->angle * PI / 180) * 10;
		(*infos)->mathi->angle -= 90;
		if ((*infos)->map->map1[(*infos)->y / 64][(*infos)->x / 64] == '1')
		{
			(*infos)->y -= sin(((*infos)->mathi->angle + 90) * PI / 180) * 10;
			(*infos)->x -= cos(((*infos)->mathi->angle + 90) * PI / 180) * 10;
			(*infos)->flag = 1;
			return;
		}
	}
	else
		rotate_angle(infos, 5);
	mlx_clear_window((*infos)->mlx, (*infos)->win);
	black_window(infos);
		draw_map(*infos);
	draw_rays(*infos);
}

void event_left(t_info **infos, int keysym)
{
	(*infos)->flag = 0;
	if (keysym == 0)
	{
		if ((*infos)->flag1)
			return;
		(*infos)->mathi->angle -= 90;
		if ((*infos)->mathi->angle > 360)
			(*infos)->mathi->angle -= 360;
		(*infos)->y += sin((*infos)->mathi->angle * PI / 180) * 10;
		(*infos)->x += cos((*infos)->mathi->angle * PI / 180) * 10;
		(*infos)->mathi->angle += 90;
		if ((*infos)->map->map1[(*infos)->y / 64][(*infos)->x / 64] == '1')
		{
			(*infos)->y -= sin(((*infos)->mathi->angle - 90) * PI / 180) * 10;
			(*infos)->x -= cos(((*infos)->mathi->angle - 90) * PI / 180) * 10;
			(*infos)->flag1 = 1;
			return;
		}
	}
	else
		rotate_angle(infos, -5);
	mlx_clear_window((*infos)->mlx, (*infos)->win);
	black_window(infos);
		draw_map(*infos);
	draw_rays(*infos);
}

void event_up(t_info **infos)
{
	(*infos)->flag = 0;
	(*infos)->flag1 = 0;
	(*infos)->mathi->delta_x = cos((*infos)->mathi->angle * PI / 180) * 10;
	(*infos)->mathi->delta_y = sin((*infos)->mathi->angle * PI / 180) * 10;
	(*infos)->y += (*infos)->mathi->delta_y;
	(*infos)->x += (*infos)->mathi->delta_x;
	if ((*infos)->map->map1[(*infos)->y / 64][(*infos)->x / 64] == '1')
	{
		(*infos)->y -= (*infos)->mathi->delta_y;
		(*infos)->x -= (*infos)->mathi->delta_x;
		return;
	}
	mlx_put_image_to_window((*infos)->mlx, (*infos)->win, (*infos)->play, (*infos)->x, (*infos)->y);
	mlx_clear_window((*infos)->mlx, (*infos)->win);
	black_window(infos);
		draw_map(*infos);
	draw_rays(*infos);
}

void event_down(t_info **infos)
{
	(*infos)->flag = 0;
	(*infos)->flag1 = 0;
	(*infos)->mathi->delta_x = cos((*infos)->mathi->angle * PI / 180) * 10;
	(*infos)->mathi->delta_y = sin((*infos)->mathi->angle * PI / 180) * 10;
	(*infos)->y -= (*infos)->mathi->delta_y;
	(*infos)->x -= (*infos)->mathi->delta_x;
	if ((*infos)->map->map1[(*infos)->y / 64][(*infos)->x / 64] == '1')
	{
		(*infos)->y += (*infos)->mathi->delta_y;
		(*infos)->x += (*infos)->mathi->delta_x;
		return;
	}
	mlx_put_image_to_window((*infos)->mlx, (*infos)->win, (*infos)->play, (*infos)->x, (*infos)->y);
	mlx_clear_window((*infos)->mlx, (*infos)->win);
	black_window(infos);
		draw_map(*infos);
	draw_rays(*infos);
}

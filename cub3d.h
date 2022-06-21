/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:20:13 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/21 12:25:56 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <stdio.h>
#include <math.h>

#define WIN_WIDTH 1440
#define WIN_HEIGHT 900
#define BUFFER_SIZE 1024
#define WALL_SIZE 500
#define PI 3.141592653589793238

typedef struct t_info
{
	void *mlx;
	void *win;
	void *img;
	int width;
	int height;
	char *addr;
	int bpp;
	int		size_l;
	int endian;
	char	**map;
	char **map1;
	int north;
	int west;
	int east;
	int distance_wall;
	int south;
	char *no_text;
	char *so_text;
	char *we_text;
	char *ea_text;
	int ceiling;
	int floor;
	int red;
	int green;
	int blue;
	void	*play;
	void	*direction;
	int	delta_x;
	int	delta_y;
	double	angle;
	int x;
	int y;
	int i;
	int j;
	int		fd;
	int maplen;
	double distance_plane;
	double distance;
	double wall_h;
	double floor1;
	double ceilling1;
}	t_info;

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);
size_t	ft_strlen(char const *str);
int		ft_strstr(char *str, char *to_find);
char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strchr(const char *str, int c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_strcmp(const char *str1, const char *str2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_getmap(t_info *infos);
int		ft_atoi(const char *str);
int		ft_isalpha(char *ch);
int		ft_isascii(char *a);
int		check_comma(t_info *infos, int j, int i);
int		check_char(char **color);
int		checkmap(t_info *infos);
void	checkmap1(t_info *infos, int *i);
void	ft_skipspace(t_info *infos, int *j, int i);
void	draw_map1(t_info *infos, int x, int y, int color);
void	draw_map(t_info *infos);
void	draw_player(t_info *infos);
void init(t_info *infos);
void	my_mlx_pixel_put(t_info *data, int x, int y, int color);
void event_right(t_info **infos, int keysym);
void event_left(t_info **infos, int keysym);
void event_up(t_info **infos);
void event_down(t_info **infos);
void	draw_rays(t_info *infos);

#endif

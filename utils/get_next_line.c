/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:21:41 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/28 12:03:37 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_free(char **frfr)
{
	free(*frfr);
	*frfr = NULL;
}

void ft_line(char **line, char **save, char **tmp)
{
	if (ft_strchr(*save, '\n') == -1)
	{
		*line = ft_strdup(*save);
		ft_free(save);
	}
	else
	{
		*line = ft_substr(*save, 0, ft_strchr(*save, '\n') + 1);
		*tmp = *save;
		*save = ft_strdup(*save + ft_strchr(*save, '\n') + 1);
		ft_free(tmp);
	}
}

char *get_next_line(int fd)
{
	static char *save;
	char *line;
	char *buff;
	char *tmp;
	int ret;

	buff = (char *)malloc(sizeof(char) * (1000 + 1));
	if (!buff)
		return (0);
	if (!save)
		save = ft_strdup("");
	ret = 1000;
	while (ret > 0 && ft_strchr(save, '\n') == -1)
	{
		ret = read(fd, buff, 1000);
		if (ret == -1)
			break;
		buff[ret] = 0;
		save = ft_strjoin(save, buff);
	}
	ft_free(&buff);
	ft_line(&line, &save, &tmp);
	if (*line == '\0')
		ft_free(&line);
	return (line);
}
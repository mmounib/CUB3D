#include "cub3d.h"

void check_first_line(t_info *infos)
{
	int j;

	j = -1;
	while (infos->map->map1[0][++j])
	{
		if (infos->map->map1[0][j] != '1' && infos->map->map1[0][j] != ' ')
		{
			printf("Error, Map Is Not Closed!!\n");
			exit(0);
		}
	}
}

void check_last_line(t_info *infos, int i)
{
	int j;

	j = -1;
	while (infos->map->map1[i][++j])
	{
		if (infos->map->map1[i][j] != '1' && infos->map->map1[i][j] != ' ')
		{
			printf("Error, Map Is Not Closed!!\n");
			exit(0);
		}
	}
}

// void	checkmap_0(t_info *infos)
// {
// 	int i;
// 	int j;

// 	i = 1;
	
// 	while (infos->map->map1[i + 1])
// 	{
// 		j = -1;
// 		while (infos->map->map1[i][++j])
// 		{
// 			// if ((ft_strchr1("0NWES",infos->map->map1[i][j])) && (!infos->map->map1[i - 1][j] || !infos->map->map1[i + 1][j] || infos->map->map1[i - 1][j] == ' ' ||
// 			// infos->map->map1[i][j + 1] == ' ' || infos->map->map1[i + 1][j] == ' '))
// 			// {
// 			// 	printf("Error, There Is a Space Or Null Beside 0!!\n");
// 			// 	exit(0);
// 			// }
// 		}
// 		i++;
// 	}
	
// }

void checkallmap(t_info *infos)
{
	int i;
	int j;

	i = 1;
	check_first_line(infos);
	while (infos->map->map1[i + 1])
	{
		j = -1;
		while (infos->map->map1[i][++j])
		{
			if ((ft_strchr1("0NWES",infos->map->map1[i][j])) && (infos->map->map1[i][0] == '0'||
			infos->map->map1[i][ft_strlen(infos->map->map1[i]) - 1] == '0'))
			{
				printf("Error, Map Is Not Closed!!\n");
				exit(0);
			}
			if ((ft_strchr1("0NWES",infos->map->map1[i][j])) && (!infos->map->map1[i - 1][j] || !infos->map->map1[i + 1][j] || infos->map->map1[i - 1][j] == ' ' ||
			infos->map->map1[i][j + 1] == ' ' || infos->map->map1[i + 1][j] == ' '))
			{
				printf("Error Inside The Map!!\n");
				exit(0);
			}
		}
		i++;
	}
	check_last_line(infos, i);
}

void add_map(t_info *infos, int x)
{
	int c;
	int j;
	
	c = 0;
	while (infos->map->map[++x])
	{
		j = -1;
		while (infos->map->map[x][++j])
			infos->map->map1[c][j] = infos->map->map[x][j];
		c++;
	}
}

void replace_map(t_info *infos, int i)
{
	int x;
	int c;
	int j;

	x = i;
	j = -1;
	infos->map->maplen = 0;
	//printf("%d\n", i);
	while (infos->map->map[++i])
		infos->map->maplen++;
	infos->map->map1 = malloc(sizeof(char *) * (infos->map->maplen + 1));
	while (++j <  infos->map->maplen)
		infos->map->map1[j] = malloc(sizeof(char) * (infos->map->map_length + 1));
	c = -1;
	while (++c < infos->map->maplen)
	{
		j = -1;
		while (++j <= infos->map->map_length)
			infos->map->map1[c][j] = 0;
	}
	infos->map->map1[c] = 0;
	add_map(infos, x);
}
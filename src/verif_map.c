/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:15:58 by nbiron            #+#    #+#             */
/*   Updated: 2024/03/12 15:25:16 by nbiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	count_char(t_complete *map, char a)
{
	int	y;
	int	i;
	int	total;

	y = 0;
	i = 0;
	total = 0;
	while (map->map[y])
	{
		i = 0;
		while (map->map[y][i])
		{
			if (map->map[y][i] == a)
				total += 1;
			if (map->map[y][i] != '1' && map->map[y][i] != '0'
				&& map->map[y][i] != 'C' && map->map[y][i] != 'E'
				&& map->map[y][i] != 'P' && map->map[y][i] != '\0'
				&& map->map[y][i] != '\n')
				return (-1);
			i++;
		}
		y++;
	}
	return (total);
}

int	count(int x, int y, t_complete *map, char a)
{
	int	r;
	int	l;
	int	u;
	int	d;

	if (x < 0 || x >= map->widthmap
		|| y < 0 || y >= map->heightmap)
		return (0);
	if (map->buf[y][x] == '1')
		return (0);
	map->buf[y][x] = '1';
	r = count(x + 1, y, map, a);
	l = count(x - 1, y, map, a);
	u = count(x, y - 1, map, a);
	d = count(x, y + 1, map, a);
	if (map->map[y][x] == a)
		return (1 + r + l + u + d);
	return (r + l + u + d);
}

void	reset_buff(t_complete map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.heightmap)
	{
		j = 0;
		while (j < map.widthmap)
		{
			map.buf[i][j] = map.map[i][j];
			j++;
		}
		i++;
	}
}

int	verif_border(t_complete map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.heightmap)
	{
		j = 0;
		while (j < map.widthmap)
		{
			if (i == 0 && map.buf[i][j] != '1')
				return (0);
			if (j == 0 && map.buf[i][j] != '1')
				return (0);
			if (i == map.widthmap && map.buf[i][j] != '1')
				return (0);
			if (i == map.heightmap && map.buf[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	verif_map(t_complete *map)
{
	int		end;
	int		spawn;

	map->valid = 1;
	if (map->widthmap < 4 || map->heightmap < 4)
	{
		free_map(map);
		exit_handler("Invalid map", NULL);
	}
	spawn = count_char(map, 'P');
	end = count_char(map, 'E');
	if (map->collectables == 0 || spawn != 1 || end != 1)
		map->valid = 0;
	reset_buff(*map);
	if (map->collectables != count(map->x, map->y, map, 'C'))
		map->valid = 0;
	reset_buff(*map);
	if (end != count(map->x, map->y, map, 'E'))
		map->valid = 0;
	reset_buff(*map);
	if (!verif_border(*map))
		map->valid = 0;
}

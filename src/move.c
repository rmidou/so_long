/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:47:32 by nbiron            #+#    #+#             */
/*   Updated: 2024/03/27 15:54:42 by nbiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	move_2(t_complete *map, int x, int y)
{
	if (map->map[y][x] != '1')
	{
		if (map->e)
		{
			map->map[map->y][map->x] = 'E';
			map->e = 0;
		}
		else
			map->map[map->y][map->x] = '0';
		map->x = x;
		map->y = y;
		if (map->map[y][x] == 'C')
			(map->counter)++;
		if (map->map[y][x] == 'E'
			&& map->collectables == map->counter)
			on_destroy(map);
		else if (map->map[y][x] == 'E')
			map->e = 1;
		map->map[y][x] = 'P';
	}
	print_map(map);
}

int	move(int key, t_complete *map)
{
	int		tx;
	int		ty;
	int		x;
	int		y;

	x = map->x;
	y = map->y;
	tx = x;
	ty = y;
	if (key == 'w')
		ty--;
	if (key == 'a')
		tx--;
	if (key == 's')
		ty++;
	if (key == 'd')
		tx++;
	if (key == 'd' || key == 's'
		|| key == 'a' || key == 'w')
		ft_printf("Moves : %i\n", ++(map->playercount));
	if (key == 65307)
		on_destroy(map);
	move_2(map, tx, ty);
	return (1);
}

void	init_hero(t_complete *map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'P')
			{
				map->x = x;
				map->y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

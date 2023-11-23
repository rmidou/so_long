/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:00:55 by nbiron            #+#    #+#             */
/*   Updated: 2023/11/23 16:00:12 by nbiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	put_img(char chara, t_complete map)
{
	if (chara == '1')
	{
		mlx_put_image_to_window(map.mlxptr, map.winptr, map.wall, map.x * 16 , map.y * 16);
	}
	if (chara == '0')
	{
		mlx_put_image_to_window(map.mlxptr, map.winptr, map.floor, map.x * 16 , map.y * 16);
	}
	if (chara == 'C')
	{
		mlx_put_image_to_window(map.mlxptr, map.winptr, map.collectable, map.x * 16 , map.y * 16);
	}
	if (chara == 'P')
	{
		mlx_put_image_to_window(map.mlxptr, map.winptr, map.hero, map.x * 16 , map.y * 16);
	}
	if (chara == 'E')
	{
		mlx_put_image_to_window(map.mlxptr, map.winptr, map.exit, map.x * 16 , map.y * 16);
	}
}

int	read_map(t_complete *map)
{
	char 	*ligne;
	int		i;

	ligne = get_next_line(map->fd);
	map->y = 0;
	while (ligne)
	{
		i = 0;
		map->x = 0;
		while (ligne[i])
		{
			put_img(ligne[i], *map);
			map->x += 1;
			i++;
		}
		map->y += 1;
		ligne = get_next_line(map->fd);
	}
	return (1);
}
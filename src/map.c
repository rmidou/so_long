/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:00:55 by nbiron            #+#    #+#             */
/*   Updated: 2023/11/27 17:08:20 by nbiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	put_img(char chara, t_complete map)
{
	if (chara == '1')
		mlx_put_image_to_window
			(map.mlxptr, map.winptr, map.wall, map.x * 64, map.y * 64);
	if (chara == '0')
		mlx_put_image_to_window
			(map.mlxptr, map.winptr, map.floor, map.x * 64, map.y * 64);
	if (chara == 'C')
		mlx_put_image_to_window
			(map.mlxptr, map.winptr, map.collectable, map.x * 64, map.y * 64);
	if (chara == 'P')
		mlx_put_image_to_window
			(map.mlxptr, map.winptr, map.hero, map.x * 64, map.y * 64);
	if (chara == 'E')
		mlx_put_image_to_window
			(map.mlxptr, map.winptr, map.exit, map.x * 64, map.y * 64);
}

void	print_map(t_complete *map)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (map->map[y])
	{
		i = 0;
		while (map->map[y][i])
		{
			map->x = i;
			map->y = y;
			put_img(map->map[y][i], *map);
			i++;
		}
		y++;
	}
	init_hero(map);
}

void	collectibles(t_complete *map)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (map->map[y])
	{
		i = 0;
		while (map->map[y][i])
		{
			if (map->map[y][i] == 'C')
				(map->collectables)++;
			i++;
		}
		y++;
	}
}

void	nb_ligne(t_complete *map, char *av)
{
	int		i;
	char	*ligne;

	ligne = get_next_line(map->fd);
	map->widthmap = ft_strlen(ligne);
	i = 0;
	while (ligne)
	{
		ligne = get_next_line(map->fd);
		i++;
	}
	close(map->fd);
	map->fd = open(av, O_RDONLY);
	map->heightmap = i;
}

int	read_map(t_complete *map, char *av)
{
	char	*ligne;
	int		y;

	y = 0;
	nb_ligne(map, av);
	ligne = get_next_line(map->fd);
	map->map = malloc(sizeof(char *) * (map->heightmap + 1));
	while (ligne)
	{
		map->map[y] = ligne;
		ligne = get_next_line(map->fd);
		y++;
	}
	map->map[y] = (char *) '\0';
	close(map->fd);
	init_hero(map);
	print_map(map);
	collectibles(map);
	return (1);
}

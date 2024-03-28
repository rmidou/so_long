/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:39:43 by nbiron            #+#    #+#             */
/*   Updated: 2024/03/12 15:30:34 by nbiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init(t_complete *map)
{
	int	width;
	int	height;

	map->mlxptr = mlx_init();
	map->winptr = mlx_new_window(map->mlxptr, 64 * map->widthmap,
			64 * map->heightmap, "marge");
	map->wall = mlx_xpm_file_to_image
		(map->mlxptr, "textures/wall.xpm", &width, &height);
	map->floor = mlx_xpm_file_to_image
		(map->mlxptr, "textures/floor.xpm", &width, &height);
	map->collectable = mlx_xpm_file_to_image
		(map->mlxptr, "textures/collectible.xpm", &width, &height);
	map->hero = mlx_xpm_file_to_image
		(map->mlxptr, "textures/hero.xpm", &width, &height);
	map->exit = mlx_xpm_file_to_image
		(map->mlxptr, "textures/exit.xpm", &width, &height);
}

void	free_map(t_complete *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	i = 0;
	while (map->buf[i])
	{
		free(map->buf[i]);
		i++;
	}
	free(map->buf);
}

int	on_destroy(t_complete *map)
{
	mlx_destroy_window(map->mlxptr, map->winptr);
	mlx_destroy_image(map->mlxptr, map->wall);
	mlx_destroy_image(map->mlxptr, map->floor);
	mlx_destroy_image(map->mlxptr, map->collectable);
	mlx_destroy_image(map->mlxptr, map->hero);
	mlx_destroy_image(map->mlxptr, map->exit);
	mlx_destroy_display(map->mlxptr);
	free(map->mlxptr);
	free_map(map);
	exit(0);
	return (0);
}

static int	on_destroyy(t_complete *map)
{
	mlx_destroy_window(map->mlxptr, map->winptr);
	mlx_destroy_image(map->mlxptr, map->wall);
	mlx_destroy_image(map->mlxptr, map->floor);
	mlx_destroy_image(map->mlxptr, map->collectable);
	mlx_destroy_image(map->mlxptr, map->hero);
	mlx_destroy_image(map->mlxptr, map->exit);
	mlx_destroy_display(map->mlxptr);
	free(map->mlxptr);
	free_map(map);
	return (0);
}

int	main(int ac, char **av)
{
	t_complete	map;

	(void)ac;
	ft_bzero(&map, sizeof(t_complete));
	map.valid = 1;
	if (read_map(&map, av[1]) == 0 || verif(av[1) == 0)
		map.valid = -1;
	if (map.valid > 0)
	{
		verif_map(&map);
		init(&map);
	}
	if (map.valid <= 0)
	{
		if (map.valid == 0)
			on_destroyy(&map);
		exit_handler("Invalid map", NULL);
	}
	print_map(&map);
	mlx_hook(map.winptr, KeyRelease, KeyReleaseMask, &move, &map);
	mlx_hook(map.winptr, DestroyNotify, StructureNotifyMask, &on_destroy, &map);
	mlx_loop(map.mlxptr);
	return (0);
}

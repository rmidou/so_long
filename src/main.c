/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:39:43 by nbiron            #+#    #+#             */
/*   Updated: 2023/11/23 16:25:25 by nbiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init(t_complete *map, char *av)
{
	int	width;
	int	height;

	map->mlxptr = mlx_init();
	map->winptr = mlx_new_window(map->mlxptr, 500, 500, "marge");
	map->wall = mlx_xpm_file_to_image(map->mlxptr, "textures/wall_1.xpm", &width, &height);
	map->floor = mlx_xpm_file_to_image(map->mlxptr, "textures/floor_1.xpm", &width, &height);
	map->collectable = mlx_xpm_file_to_image(map->mlxptr, "textures/colectible.xpm", &width, &height);
	map->hero = mlx_xpm_file_to_image(map->mlxptr, "textures/hero.xpm", &width, &height);
	map->exit = mlx_xpm_file_to_image(map->mlxptr, "textures/exit.xpm", &width, &height);
	map->x = 0;
	map->y = 0;
	map->fd = open(av, O_RDONLY);
}

int main(int ac, char **av)
{
	t_complete map;

	(void)ac;
	init(&map, av[1]);
	read_map(&map);
	mlx_loop(map.mlxptr);
	mlx_destroy_window(map.mlxptr, map.winptr);
	mlx_destroy_display(map.mlxptr);
	free(map.mlxptr);
	return (0);
}


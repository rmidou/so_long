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
	map->wall = mlx_xpm_file_to_image(map->mlxptr, "textures/wall.xpm", &width, &height);
	map->floor = mlx_xpm_file_to_image(map->mlxptr, "textures/floor.xpm", &width, &height);
	map->collectable = mlx_xpm_file_to_image(map->mlxptr, "textures/collectible.xpm", &width, &height);
	map->hero = mlx_xpm_file_to_image(map->mlxptr, "textures/hero.xpm", &width, &height);
	map->exit = mlx_xpm_file_to_image(map->mlxptr, "textures/exit.xpm", &width, &height);
	map->x = 0;
	map->y = 0;
	map->fd = open(av, O_RDONLY);
}

int	on_destroy(t_game *game)
{
	ft_free_split(game->map.data);
	ft_free_split(game->map.buff);
	destroy_texs(*game);
	free_mobs(game->mobs);
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

int main(int ac, char **av)
{
	t_complete map;

	(void)ac;
	init(&map, av[1]);
	read_map(&map);
	mlx_loop(map.mlxptr);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &on_destroy, game);
	mlx_destroy_window(map.mlxptr, map.winptr);
	mlx_destroy_display(map.mlxptr);
	free(map.mlxptr);
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:00:55 by nbiron            #+#    #+#             */
/*   Updated: 2023/11/23 16:54:37 by nbiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	put_img(char chara, t_complete map)
{
	if (chara == '1')
	{
		mlx_put_image_to_window(map.mlxptr, map.winptr, map.wall, map.x * 64 , map.y * 64);
	}
	if (chara == '0')
	{
		mlx_put_image_to_window(map.mlxptr, map.winptr, map.floor, map.x * 64 , map.y * 64);
	}
	if (chara == 'C')
	{
		mlx_put_image_to_window(map.mlxptr, map.winptr, map.collectable, map.x * 64 , map.y * 64);
	}
	if (chara == 'P')
	{
		mlx_put_image_to_window(map.mlxptr, map.winptr, map.hero, map.x * 64 , map.y * 64);
	}
	if (chara == 'E')
	{
		mlx_put_image_to_window(map.mlxptr, map.winptr, map.exit, map.x * 64 , map.y * 64);
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

int	controls(int command, t_complete *map)
{
	int	works;

	//if (command == 53)
	//	exit_point(map);
	//if (command == 13)
	//	works = keyboard_w_s(game, command);
	//if (command == 1)
	//	works = keyboard_w_s(game, command);
	//if (command == 0)
	//	works = keyboard_a_d(game, command);
	//if (command == 2)
	//	works = keyboard_a_d(game, command);
	//if (works)
	//	adding_in_graphics(game);
	return (1);
}

// char *addc(char *ligne, char chara)
// {
// 	char *new;
// 	int	i;

// 	i = 0;
// 	new = malloc(sizeof(char) * (ft_strlen(ligne) + 2));
// 	while (ligne[i])
// 	{
// 		new[i] = ligne[i];
// 		i++;
// 	}
// 	new[i] = chara;
// 	new[i + 1] = '\n';
// 	return (new);
// }

// int	read_map(t_complete *map)
// {
// 	char 	*ligne;
// 	char	**tab;
// 	int		i;
// 	int		y;

// 	ligne = get_next_line(map->fd);
// 	y = 0;
// 	while (ligne)
// 	{
// 		i = 0;
// 		while (ligne[i])
// 		{
// 			if (ligne[i] != '\n')
// 				tab[y] = addc(tab[y] ,ligne[i]);
// 		}
// 		free(ligne);
// 		ligne = get_next_line(map->fd);
// 		y++;
// 	}
// 	return (1);
// }

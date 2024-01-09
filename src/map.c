/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:00:55 by nbiron            #+#    #+#             */
/*   Updated: 2024/01/09 19:19:37 by nbiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// void	print_mapp(t_complete *map)
// {
// 	int	y;
// 	int	i;

// 	y = 0;
// 	i = 0;
// 	while (map->buf[y])
// 	{
// 		i = 0;
// 		while(map->buf[y][i])
// 		{
// 			ft_printf("%c", map->buf[y][i]);
// 			i++;
// 		}
// 		y++;
// 	}
// 	ft_printf("C : %d || sur : %d", map->collectables, map->counter);
// }

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
	display_info(*map);
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
	if (ligne)
		map->widthmap = ft_strlen(ligne) - 1;
	free(ligne);
	i = 0;
	while (ligne)
	{
		ligne = get_next_line(map->fd);
		free(ligne);
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
	map->fd = open(av, O_RDONLY);
	nb_ligne(map, av);
	ligne = get_next_line(map->fd);
	map->map = malloc(sizeof(char *) * (map->heightmap + 1));
	map->buf = malloc(sizeof(char *) * (map->heightmap + 1));
	while (ligne)
	{
		map->map[y] = ligne;
		map->buf[y] = ft_strdup(ligne);
		ligne = get_next_line(map->fd);
		y++;
	}
	map->map[y] = NULL;
	map->buf[y] = NULL;
	close(map->fd);
	init_hero(map);
	collectibles(map);
	return (1);
}

void	exit_handler(char *msg, char *info)
{
	ft_putstr_fd("Error: ", 2);
	if (info)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(info, 2);
	}
	else
		ft_putendl_fd(msg, 2);
	exit(-1);
}

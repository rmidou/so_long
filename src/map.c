/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:00:55 by nbiron            #+#    #+#             */
/*   Updated: 2024/01/09 15:55:13 by nbiron           ###   ########.fr       */
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

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	display_info(t_complete map)
{
	char	*s;
	char	*num1;
	char	*num2;

	num1 = ft_itoa(map.counter);
	num2 = ft_itoa(map.playercount);
	s = ft_strjoin("Moves: ", num2);
	mlx_string_put(map.mlxptr, map.winptr, 10, 10, trgb(255, 255, 255, 255), s);
	free(s);
	s = ft_strjoin("Collected: ", num1);
	free(num1);
	free(num2);
	mlx_string_put(map.mlxptr, map.winptr, 10, 20, trgb(255, 255, 255, 255), s);
	free(s);
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
				total+= 1;
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

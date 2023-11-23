/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:39:43 by nbiron            #+#    #+#             */
/*   Updated: 2023/11/23 15:59:40 by nbiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

int main(int ac, char **av)
{
	t_complete map;
	int	width;
	int	height;
	int	i;
	int	y;
 
	(void)ac;
	i = 1;
	y = 1;
	map.mlxptr = mlx_init();
	map.winptr = mlx_new_window(map.mlxptr, 500, 500, "marge");
	map.wall = mlx_xpm_file_to_image(map.mlxptr, "textures/wall_1.xpm", &width, &height);
	map.floor = mlx_xpm_file_to_image(map.mlxptr, "textures/floor_1.xpm", &width, &height);
	map.collectable = mlx_xpm_file_to_image(map.mlxptr, "textures/colectible.xpm", &width, &height);
	map.hero = mlx_xpm_file_to_image(map.mlxptr, "textures/hero.xpm", &width, &height);
	map.exit = mlx_xpm_file_to_image(map.mlxptr, "textures/exit.xpm", &width, &height);
	map.x = 1;
	map.y = 1;
	map.fd = open(av[1], O_RDONLY);
	//img.img = mlx_new_image(mlx_ptr, 600, 400);
	//img.addr = mlx_get_data_addr(img.img, &(img.bits_per_pixel), &(img.line_length), &(img.endian));
	read_map(&map);
	mlx_loop(map.mlxptr);
	//while (1);
	// mlx_destroy_window(mlx_ptr, win_ptr);
	// mlx_destroy_display(mlx_ptr);
	// free(mlx_ptr);
	return (0);
}


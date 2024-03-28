/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:19:45 by nbiron            #+#    #+#             */
/*   Updated: 2024/03/28 11:11:33 by nbiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	put_img(char chara, t_complete map)
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

int	verif(char *av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	if (i > 3 && av[i - 1] == 'r' && av[i - 2] == 'e'
		&& av[i - 3] == 'b' && av[i - 4] == '.')
		return (1);
	return (0);
}

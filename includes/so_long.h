/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbiron <nbiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:21:35 by nbiron            #+#    #+#             */
/*   Updated: 2024/03/12 13:46:12 by nbiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>

typedef struct t_start
{
	int		fd;
	int		heightmap;
	int		widthmap;
	int		playercount;
	int		x_map;
	int		y_map;
	int		x;
	int		y;
	int		e;
	int		counter;
	int		collectables;
	int		valid;

	char	**map;
	char	**buf;

	void	*floor;
	void	*wall;
	void	*hero;
	void	*exit;
	void	*collectable;
	void	*mlxptr;
	void	*winptr;

}	t_complete;

int		read_map(t_complete *map, char *av);
int		controls(int command, t_complete *map);
int		on_destroy(t_complete *map);
int		move(int key, t_complete *map);
void	print_map(t_complete *map);
void	init_hero(t_complete *map);
void	verif_map(t_complete *map);
void	exit_handler(char *msg, char *info);
void	free_map(t_complete *map);
void	put_img(char chara, t_complete map);
void	display_info(t_complete map);
int		verif(char *av);

#endif

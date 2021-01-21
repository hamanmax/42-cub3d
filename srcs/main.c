/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:40:25 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 20:56:33 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_cub(t_cub *map)
{
	int		i;

	i = 0;
	while (i <= map->mapsize.y)
	{
		free(map->map[i]);
		i++;
	}
	free(map->sprite);
	free(map->screenpx);
	free(map);
}

void	ft_init_struct(t_cub *map, int code)
{
	int		v;

	if (code == 0)
	{
		map->colorfloor = -1;
		map->colorsky = -1;
		map->mlx.ptr = mlx_init();
	}
	if (code == 1)
	{
		map->pla.orientation =
		map->map[(int)map->pla.pos.x][(int)map->pla.pos.y];
		map->pla.pos.x += 0.5;
		map->pla.pos.y += 0.5;
		set_dir_plane_vector(map);
		set_data(map);
		load_sprite(map);
		map->mlx.img =
		mlx_new_image(map->mlx.ptr, map->screen.x, map->screen.y);
		map->mlx.data = (int *)mlx_get_data_addr(map->mlx.img, &v, &v, &v);
		map->mlx.win =
		mlx_new_window(map->mlx.ptr, map->screen.x, map->screen.y, "Cub3d");
	}
}

int		ft_key_press(int keycode, t_cub *map)
{
	if (keycode == K_W)
		map->move.forward = 1;
	if (keycode == K_S)
		map->move.backward = 1;
	if (keycode == K_A)
		map->move.leftside = 1;
	if (keycode == K_D)
		map->move.rightside = 1;
	if (keycode == K_Q)
		map->move.leftrot = 1;
	if (keycode == K_E)
		map->move.rightrot = 1;
	if (keycode == K_ESC)
		map->move.close = 1;
	return (1);
}

int		ft_key_release(int keycode, t_cub *map)
{
	if (keycode == K_W)
		map->move.forward = 0;
	if (keycode == K_S)
		map->move.backward = 0;
	if (keycode == K_A)
		map->move.leftside = 0;
	if (keycode == K_D)
		map->move.rightside = 0;
	if (keycode == K_Q)
		map->move.leftrot = 0;
	if (keycode == K_E)
		map->move.rightrot = 0;
	return (1);
}

int		main(int argc, char **argv)
{
	int		i;
	t_cub	*map;

	i = 0;
	map = ft_calloc(1, sizeof(t_cub));
	ft_init_struct(map, 0);
	parse_file_cub(map, argv, argc);
	ft_init_struct(map, 1);
	ft_printf("file valid\n");
	map->screenpx = malloc(map->screen.x * map->screen.y * sizeof(int));
	mlx_hook(map->mlx.win, 2, 1L << 0, &ft_key_press, map);
	mlx_hook(map->mlx.win, 3, 1L << 1, &ft_key_release, map);
	mlx_loop_hook(map->mlx.ptr, &main_loop, map);
	mlx_loop(map->mlx.ptr);
	return (0);
}

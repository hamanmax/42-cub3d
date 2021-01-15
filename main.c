/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:40:25 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/15 16:49:21 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_dir_plane_vector(t_cub *map)
{
	const char c = map->player.orientation;

	if (c == 'N')
	{
		map->player.dir.x = -1;
		map->player.plane.y = 0.66;
	}
	if (c == 'S')
	{
		map->player.dir.x = 1;
		map->player.plane.y = -0.66;
	}
	if (c == 'E')
	{
		map->player.dir.y = -1;
		map->player.plane.x = 0.66;
	}
	if (c == 'W')
	{
		map->player.dir.y = 1;
		map->player.plane.x = -0.66;
	}
}

void set_data(t_cub *map)
{
	int bpp;
	int endian;
	int line_size;
	int i;
	void *img_txt;

	i = 0;

	while (i < TEXTURE_COUNT)
	{
		img_txt = mlx_xpm_file_to_image(map->mlx.ptr,map->text[i],&map->mlx.w[i],&map->mlx.h[i]);
		map->mlx.data_text[i] = (int *)mlx_get_data_addr(img_txt,&bpp,&line_size,&endian);
		i++;
	}
}

void free_all(t_cub *map)
{
	int i;

	i = 0;
	while (map->map[i])
	{
		free(map->map[i]);
		i++;
	}
	free(map);
}

void ft_init_struct(t_cub *map, int code)
{
	if (code == 0)
	{
		map->colorfloor = -1;
		map->colorsky = -1;
		map->mlx.ptr = mlx_init(); // Potentiellement a enlever //
	}
	if (code == 1)
	{
		map->player.pos.x += 0.5;
		map->player.pos.y += 0.5;
		map->player.orientation = 
		map->map[(int)map->player.pos.x][(int)map->player.pos.y];
		set_dir_plane_vector(map);
		set_data(map);
		map->ray.pos.x = map->player.pos.x;
		map->ray.pos.y = map->player.pos.y;
	}
}

int		main(int argc, char **argv)
{
	int i;

	i = 0;
	t_cub			*map;

	map = ft_calloc(1,sizeof(t_cub));
	ft_init_struct(map, 0);
	parse_file_cub(map, argv, argc);
	ft_init_struct(map, 1);
	printf("file valid\n");
	raycasting(map);
	//create_new_black_window(map);
	//mlx_loop(map->mlx.ptr);
	free_all(map);
	return (0);
}

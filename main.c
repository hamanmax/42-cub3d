/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:40:25 by mhaman            #+#    #+#             */
/*   Updated: 2020/10/15 10:15:11 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int		main(int argc, char **argv)
{
	int i;

	i = 0;
	t_cub			*map;

	map = ft_calloc(1,sizeof(t_cub));
	map->colorfloor = -1;
	map->colorsky = -1;
	map->mlx.ptr = mlx_init();
	parse_file_cub(map, argv, argc);
	printf("file valid\n");
	set_data(map);
	map->ray = ft_calloc(map->screen.x, sizeof(t_ray));
	map->spr = ft_calloc(map->nbsprite, sizeof(t_ray));
	raytracing(map);
	create_new_black_window(map);
	mlx_loop(map->mlx.ptr);
	free_all(map);
	return (0);
}

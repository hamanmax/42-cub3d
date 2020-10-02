/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:40:25 by mhaman            #+#    #+#             */
/*   Updated: 2020/09/30 18:32:44 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

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

	ft_bzero((map = malloc(sizeof(t_cub))), sizeof(t_cub));
	map->colorfloor = -1;
	map->colorsky = -1;
	map->mlx.ptr = mlx_init();
	parse_file_cub(map, argv, argc);
	printf("file valid\n");
	map->ray = ft_calloc(map->screen.x,sizeof(t_ray));
	raytracing(map);
	projection(map);
	create_new_black_window(map);
	mlx_loop(map->mlx.ptr);
	free_all(map);
	return (0);
}

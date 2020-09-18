/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:40:25 by mhaman            #+#    #+#             */
/*   Updated: 2020/09/18 11:51:08 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

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
	ft_bzero(map->ray = malloc(map->screen.x * sizeof(t_ray)),sizeof(t_ray));
	raytracing(map);
/* 	while (i < map->screen.x)
	{
		dprintf(1,"%f\t%f\t%f\n",map->ray[i].oppose,map->ray[i].angle,map->ray[i].pointpos.y);
		i++;
	} */
	projection(map);
	create_new_black_window(map);
	mlx_loop(map->mlx.ptr);
	free(map);
	return (0);
}

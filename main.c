/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:40:25 by mhaman            #+#    #+#             */
/*   Updated: 2020/08/25 23:50:35 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

int		main(int argc, char **argv)
{
	t_cub			*map;
	t_ray			ray[360];

	ft_bzero(ray, sizeof(t_ray) * 360);
	ft_bzero((map = malloc(sizeof(t_cub))), sizeof(t_cub));
	map->colorfloor = -1;
	map->colorsky = -1;
	parse_file_cub(map, argv, argc);
	printf("file valid\n");
	raytracing(map, ray);
	projection(map, ray);
    create_new_black_window(map,ray);
	free(map);
	return (0);
}

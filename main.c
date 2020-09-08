/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:40:25 by mhaman            #+#    #+#             */
/*   Updated: 2020/09/07 16:10:16 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

int		main(int argc, char **argv)
{
	t_cub			*map;
	ft_bzero((map = malloc(sizeof(t_cub))), sizeof(t_cub));
	map->colorfloor = -1;
	map->colorsky = -1;
	parse_file_cub(map, argv, argc);
	printf("file valid\n");
	ft_bzero(map->colonne = malloc(map->screen.x * sizeof(t_ray)),sizeof(t_ray));
	raytracing(map);
	projection(map);
    create_new_black_window(map);
	free(map);
	return (0);
}

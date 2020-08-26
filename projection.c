/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 14:49:25 by mhaman            #+#    #+#             */
/*   Updated: 2020/08/26 12:11:21 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void    calc_correct_distance(t_cub *map, t_ray *ray,int i)
{
    float pi;

    pi = 3.14159265359;
    if (i < map->projection_id.y - 30)
    ray[i].walldist += cos((30 * (pi / 180)));
    if (i >= map->projection_id.y - 30)
    ray[i].walldist += cos((-30 * (pi / 180)));
    ray[i].wallheight = (0.5/ray[i].walldist)*map->projectiondist;
}

int		projection(t_cub *map, t_ray *ray)
{
    float	pi;
    int   i;

    pi = 3.14159265359;
    map->projection_center.x = map->screen.x / 2;
    map->projection_center.y = map->screen.y / 2;
    map->projectiondist = (map->screen.x / 2) / tanf((30 * (pi / 180)));
    if (check_player_orientation(map) == 0)
        map->projection_id = set_wall_pos(15, 78);
    if (check_player_orientation(map) == 1)
        map->projection_id = set_wall_pos(195, 258);
    if (check_player_orientation(map) == 2)
        map->projection_id = set_wall_pos(285, 348);
    if (check_player_orientation(map) == 3)
        map->projection_id = set_wall_pos(105, 168);
    i = map->projection_id.x;
    while (i <= map->projection_id.y)
	{
        calc_correct_distance(map, ray, i);
		i++;
	}
}

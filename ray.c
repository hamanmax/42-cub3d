/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray[i].c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:59:58 by mhaman            #+#    #+#             */
/*   Updated: 2020/08/09 11:20:16 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "cub3d.h"

t_float	set_wall_pos(float x, float y)
{
	t_float	wp;

	wp.x = (int)x;
	wp.y = (int)y;
	return (wp);
}

t_float	set_ray_pos(float x, float y)
{
	t_float	wp;

	wp.x = x;
	wp.y = y;
	return (wp);
}

int calc_del(t_ray ray)
{
	int t;

	t = 0;
	if (ray.oppose > 0)
		t = ceilf(ray.oppose) * -1;
	if (ray.oppose < 0)
		t = floorf(ray.oppose) * -1;
	return (t);
}

float	calc_t(t_ray *ray, t_cub *map, int i)
{
	t_float P[5];

	P[1] = ray[i].wallpos[0];
	P[2] = ray[i].wallpos[1];
	P[3] = map->player_pos;
	P[4] = ray[i].raypos[1];
	ray[i].t = ((P[1].y - P[3].y)*(P[3].x - P[4].x) - (P[1].x - P[3].x)*(P[3].y - P[4].y)) / ((P[1].y - P[2].y)*(P[3].x - P[4].x) - (P[1].x - P[2].x)*(P[3].y - P[4].y));
	return(ray[i].t);
}

int		check_player_orientation(t_cub *map)
{
	if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'N')
		return (0);
	else if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'S')
		return (1);
	else if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'E')
		return (2);
	else if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'W')
		return (3);
	return (-1);
}

float	check_wall_north_up(t_cub *map, t_ray *ray, int i)
{
	ray[i].wallpos[0] = set_wall_pos(ray[i].raypos[0].x, ray[i].raypos[0].y);
	ray[i].wallpos[1] = set_wall_pos(ray[i].raypos[0].x, ray[i].raypos[0].y + 1);
	if (calc_t(ray, map, i) > 0 && ray[i].t <= 1)
		return (ray[i].t);
	return ((ray[i].t = 0));
}

float	check_wall_north_side(t_cub *map, t_ray *ray, int i)
{
	ray[i].wallpos[0].x = (int)ray[i].raypos[0].x;
	ray[i].wallpos[0].y = (int)ray[i].raypos[0].y + ceilf(ray[i].oppose);
	ray[i].wallpos[1].x = (int)ray[i].raypos[0].x + 1;
	ray[i].wallpos[1].y = (int)ray[i].raypos[0].y + ceilf(ray[i].oppose);
	if (calc_t(ray, map, i) > 0 && ray[i].t <= 1)
	
		return (ray[i].t);
	return ((ray[i].t = 0));
}

float	check_wall_east_up(t_cub *map, t_ray *ray, int i)
{
	ray[i].wallpos[0] = set_wall_pos(ray[i].raypos[0].x + ceilf(ray[i].oppose), ray[i].raypos[0].y);
	ray[i].wallpos[1] = set_wall_pos(ray[i].raypos[0].x + ceilf(ray[i].oppose), ray[i].raypos[0].y + 1);
	if (calc_t(ray, map, i) > 0 && ray[i].t <= 1)
		return (ray[i].t);
	return ((ray[i].t = 0));
}

float	check_wall_east_side(t_cub *map, t_ray *ray, int i)
{
	ray[i].wallpos[0].x = (int)ray[i].raypos[0].x;
	ray[i].wallpos[0].y = (int)ray[i].raypos[0].y + 1;
	ray[i].wallpos[1].x = (int)ray[i].raypos[0].x + 1;
	ray[i].wallpos[1].y = (int)ray[i].raypos[0].y + 1;
	if (calc_t(ray, map, i) > 0 && ray[i].t <= 1)
		return (ray[i].t);
	return ((ray[i].t = 0));
}

float	check_wall_south_up(t_cub *map, t_ray *ray, int i)
{
	ray[i].wallpos[0] = set_wall_pos(ray[i].raypos[0].x + 1, ray[i].raypos[0].y);
	ray[i].wallpos[1] = set_wall_pos(ray[i].raypos[0].x + 1, ray[i].raypos[0].y + 1);
	if (calc_t(ray, map, i) > 0 && ray[i].t <= 1)
		return (ray[i].t);
	return ((ray[i].t = 0));
}

float	check_wall_south_side(t_cub *map, t_ray *ray, int i)
{
	ray[i].wallpos[0].x = (int)ray[i].raypos[0].x;
	ray[i].wallpos[0].y = (int)ray[i].raypos[0].y + ceilf(ray[i].oppose);
	ray[i].wallpos[1].x = (int)ray[i].raypos[0].x + 1;
	ray[i].wallpos[1].y = (int)ray[i].raypos[0].y + ceilf(ray[i].oppose);
	if (calc_t(ray, map, i) > 0 && ray[i].t <= 1)
		return (ray[i].t);
	return ((ray[i].t = 0));
}

float	check_wall_west_up(t_cub *map, t_ray *ray, int i)
{
	//printf("%f\n",ceilf(ray[i].oppose));
	ray[i].wallpos[0] = set_wall_pos(ray[i].raypos[0].x + ceilf(ray[i].oppose), ray[i].raypos[0].y);
	ray[i].wallpos[1] = set_wall_pos(ray[i].raypos[0].x + ceilf(ray[i].oppose), ray[i].raypos[0].y + 1);
	//if (i == 357)
	//printf("%f\t%f\n",ray[i].wallpos[0].x,ray[i].wallpos[0].y);
	if (calc_t(ray, map, i) > 0 && ray[i].t <= 1)
		return (ray[i].t);
	return ((ray[i].t = 0));
}

float	check_wall_west_side(t_cub *map, t_ray *ray, int i)
{
	ray[i].wallpos[0].x = (int)ray[i].raypos[0].x;
	ray[i].wallpos[0].y = (int)ray[i].raypos[0].y;
	ray[i].wallpos[1].x = (int)ray[i].raypos[0].x + 1;
	ray[i].wallpos[1].y = (int)ray[i].raypos[0].y;
	if (calc_t(ray, map, i) > 0 && ray[i].t <= 1)
		return (ray[i].t);
	return ((ray[i].t = 0));
}


void	check_wall_north(t_cub *map, t_ray *ray,int i)
{
	while (map->map[(int)ray[i].raypos[0].x][(int)ray[i].raypos[0].y] != '1')
	{
		ray[i].raypos[1] = set_ray_pos(ray[i].raypos[0].x - 1, ray[i].raypos[0].y + ray[i].oppose);
		if ((int)ray[i].raypos[1].y != (int)ray[i].raypos[0].y) /* S'il rentre la dedans c'est qu'il est en +1 +1*/
		{
			if (map->map[(int)ray[i].raypos[1].x][(int)ray[i].raypos[0].y] == '1') /* si la case au dessus est = a un 1 */
				if (check_wall_north_up(map, ray, i) != 0)
					break;
			if (map->map[(int)ray[i].raypos[0].x][(int)ray[i].raypos[1].y] == '1') /* si la case du cote est = a un 1 */
			{
					if (check_wall_north_side(map, ray, i) != 0)
						break;
			}
		}
		ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x, ray[i].raypos[1].y);
	}
	if (ray[i].t == 0)
	{
		ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x + 1, ray[i].raypos[1].y);
		check_wall_north_up(map, ray, i);
		if (ray[i].t == 0 && ray[i].angle != 45)
		{
		ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x, (ray[i].raypos[1].y + calc_del(ray[i])));
			check_wall_north_side(map, ray, i);
		}
	}
}

void	check_wall_east(t_cub *map, t_ray *ray,int i)
{
	while (map->map[(int)ray[i].raypos[0].x][(int)ray[i].raypos[0].y] != '1')
	{
		ray[i].raypos[1] = set_ray_pos(ray[i].raypos[0].x + ray[i].oppose, ray[i].raypos[0].y + 1);
		if ((int)ray[i].raypos[1].x != (int)ray[i].raypos[0].x) /* S'il rentre la dedans c'est qu'il est en +1 +1*/
		{
			if (map->map[(int)ray[i].raypos[1].x][(int)ray[i].raypos[0].y] == '1') /* si la case au dessus est = a un 1 */
				if (check_wall_east_up(map, ray, i) != 0)
					break;
			if (map->map[(int)ray[i].raypos[0].x][(int)ray[i].raypos[1].y] == '1') /* si la case du cote est = a un 1 */
			{
					if (check_wall_east_side(map, ray, i) != 0)
						break;
			}
		}
		ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x, ray[i].raypos[1].y);
	}
	if (ray[i].t == 0)
	{
		ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x + calc_del(ray[i]), ray[i].raypos[1].y);
		check_wall_east_up(map, ray, i);
		if (ray[i].t == 0 && ray[i].angle != 45)
		{
			ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x , ray[i].raypos[1].y - 1);
			check_wall_east_side(map, ray, i);
		}
	}
}

void	check_wall_south(t_cub *map, t_ray *ray,int i)
{
	while (map->map[(int)ray[i].raypos[0].x][(int)ray[i].raypos[0].y] != '1')
	{
		ray[i].raypos[1] = set_ray_pos(ray[i].raypos[0].x + 1, ray[i].raypos[0].y - ray[i].oppose);
		if ((int)ray[i].raypos[1].y != (int)ray[i].raypos[0].y) /* S'il rentre la dedans c'est qu'il est en +1 +1*/
		{
			if (map->map[(int)ray[i].raypos[1].x][(int)ray[i].raypos[0].y] == '1') /* si la case au dessus est = a un 1 */
				if (check_wall_south_up(map, ray, i) != 0)
					break;
			if (map->map[(int)ray[i].raypos[0].x][(int)ray[i].raypos[1].y] == '1') /* si la case du cote est = a un 1 */
			{
					if (check_wall_south_side(map, ray, i) != 0)
						break;
			}
		}
		ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x, ray[i].raypos[1].y);
	}
	if (ray[i].t == 0)
	{
		ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x - 1, ray[i].raypos[1].y);
		check_wall_south_up(map, ray, i);
		if (ray[i].t == 0 && ray[i].angle != 45)
		{
		ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x, (ray[i].raypos[1].y));
			check_wall_south_side(map, ray, i);
		}
	}
}

void	check_wall_west(t_cub *map, t_ray *ray,int i)
{
	while (map->map[(int)ray[i].raypos[0].x][(int)ray[i].raypos[0].y] != '1')
	{
		ray[i].raypos[1] = set_ray_pos(ray[i].raypos[0].x + ray[i].oppose, ray[i].raypos[0].y - 1);
		if ((int)ray[i].raypos[1].x != (int)ray[i].raypos[0].x) /* S'il rentre la dedans c'est qu'il est en +1 +1*/
		{
			if (map->map[(int)ray[i].raypos[1].x][(int)ray[i].raypos[0].y] == '1') /* si la case au dessus est = a un 1 */
				if (check_wall_west_up(map, ray, i) != 0)
					break;
			if (map->map[(int)ray[i].raypos[0].x][(int)ray[i].raypos[1].y] == '1') /* si la case du cote est = a un 1 */
			{
					if (check_wall_west_side(map, ray, i) != 0)
						break;
			}
		}
		ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x, ray[i].raypos[1].y);
	}
	if (ray[i].t == 0)
	{
		ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x + calc_del(ray[i]), ray[i].raypos[1].y);
		check_wall_west_up(map, ray, i);
		if (ray[i].t == 0 && ray[i].angle != 45)
		{
			ray[i].raypos[0] = set_ray_pos(ray[i].raypos[1].x, ray[i].raypos[1].y + 1);
			check_wall_west_side(map, ray, i);
		}
	}
}

int		check_wall_pos(t_cub *map, t_ray *ray,int i)
{
	ray[i].raypos[0] = map->player_pos;
	ray[i].raypos[1] = ray[i].raypos[0];
	if (i >= 0 && i < 90)
		check_wall_north(map, ray, i);
	if (i >= 90 && i < 180)
		check_wall_east(map, ray, i);
	if (i >= 180 && i < 270)
		check_wall_south(map, ray, i);
	if (i >= 270 && i < 360)
		check_wall_west(map, ray, i);
	return (0);
}

void		draw_base_ray(t_cub *map, t_ray *ray)
{
	int		i;
	int		angle;
	float	pi;

	pi = 3.14159265359;
	angle = 45;
	i = 0;
	while(i < 360)
	{
		ray[i].id = i;
		ray[i].angle = angle;
		ray[i].oppose = tan(((angle) * (pi / 180)));
		if ((i >= 0 && i < 45) || (i >= 90 && i < 135) || (i >= 225 && i < 270)
		|| (i >= 315 && i < 360))
			ray[i].oppose = -1 * tan(((angle) * (pi / 180)));
		if ((i >= 45 && i < 90) || (i >= 135 && i < 180) 
		|| (i >= 225 && i < 270) || (i >= 315 && i < 360))
			angle += 2;
		angle --;
		check_wall_pos(map, ray, i);
		i++;
	}
}

int raytracing(t_cub *map)
{
	int		i;
	t_ray	ray[360];
	
	i = 0;
	ft_bzero(ray,sizeof(t_ray) * 360);
	map->player_pos.x = map->player_pos_base.x + 0.5;
	map->player_pos.y = map->player_pos_base.y + 0.5;
	draw_base_ray(map, ray);
	while(i < 360)
	{
		//printf("%f\n",floorf(ray[i].oppose));
		//if (ray[i].t != 0 || i == 2000)
			//printf("Id=%d\tT=%f\n\nRpos=\t(%f,%f)\nPpos=\t(%f,%f)\nWpos1=\t(%f,%f)\nWpos2=\t(%f,%f)\n\n\n",ray[i].id,ray[i].t,ray[i].raypos[1].x,ray[i].raypos[1].y,map->player_pos.x,map->player_pos.y,ray[i].wallpos[0].x,ray[i].wallpos[0].y,ray[i].wallpos[1].x,ray[i].wallpos[1].y);
		i++;
	}
	return (0);
}

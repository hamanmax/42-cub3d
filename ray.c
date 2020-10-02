/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:03:13 by mhaman            #+#    #+#             */
/*   Updated: 2020/10/02 21:49:02 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <assert.h>

double set_player_orientation(t_cub *map, double i)
{
	if (i != 0)
		return (i);
	if (map->map[map->player.pos_base.x][map->player.pos_base.y] == 'N')
		return (0);
	if (map->map[map->player.pos_base.x][map->player.pos_base.y] == 'E')
		return (90);
	if (map->map[map->player.pos_base.x][map->player.pos_base.y] == 'S')
		return (180);
	if (map->map[map->player.pos_base.x][map->player.pos_base.y] == 'W')
		return (270);
	return (0);
}

t_float set_wall_pos(float x, float y)
{
	t_float wp;

	wp.x = (int)x;
	wp.y = (int)y;
	return (wp);
}

t_float set_ray_pos(float x, float y)
{
	t_float wp;

	wp.x = x;
	wp.y = y;
	return (wp);
}

int calc_del(t_ray ray)
{
	int t;

	t = 0;
	t = 0;
	if (ray.tan.oppose > 0)
		t = ceilf(ray.tan.oppose) * -1;
	if (ray.tan.oppose < 0)
		t = floorf(ray.tan.oppose) * -1;
	return (t);
}

double calc_t(t_ray *r, t_cub *map)
{
	t_float p[5];

	p[1] = r[0].wallpos[0];
	p[2] = r[0].wallpos[1];
	p[3] = map->player.pos;
	p[4] = r[0].pos[1];
	r[0].t = ((p[1].y - p[3].y) *
				  (p[3].x - p[4].x) -
			  (p[1].x - p[3].x) *
				  (p[3].y - p[4].y)) /
			 ((p[1].y - p[2].y) *
				  (p[3].x - p[4].x) -
			  (p[1].x - p[2].x) *
				  (p[3].y - p[4].y));
	return (r[0].t);
}

double set_wall_north_south(t_ray *r, t_cub *map, char c)
{
	const t_float *rp = r[0].pos;
	const double op = r[0].tan.oppose;

	if (c == 'N')
	{
		r[0].wallpos[0] = set_wall_pos(rp[0].x, rp[0].y);
		r[0].wallpos[1] = set_wall_pos(rp[0].x, rp[0].y + 1);
		if (calc_t(r, map) > 0 && (r[0].t <= 1))
			return (r[0].t);
		return ((r[0].t = 0));
	}
	if (c == 'S')
	{
		r[0].wallpos[0] = set_wall_pos(rp[0].x + 1, rp[0].y);
		r[0].wallpos[1] = set_wall_pos(rp[0].x + 1, rp[0].y + 1);
		if (calc_t(r, map) > 0 && (r[0].t <= 1))
			return (r[0].t);
		return ((r[0].t = 0));
	}
	r[0].wallpos[0] = set_wall_pos(rp[0].x, rp[0].y + ceilf(op));
	r[0].wallpos[1] = set_wall_pos(rp[0].x + 1, rp[0].y + ceilf(op));
	if (calc_t(r, map) > 0 && (r[0].t <= 1))
		return (r[0].t);
	return ((r[0].t = 0));
}

double set_wall_east_west(t_ray *r, t_cub *map, char c)
{
	const t_float *rp = r[0].pos;
	const double op = r[0].tan.oppose;

	if (c == 'W')
	{
		r[0].wallpos[0] = set_wall_pos(rp[0].x, rp[0].y);
		r[0].wallpos[1] = set_wall_pos(rp[0].x + 1, rp[0].y);
		if (calc_t(r, map) > 0 && (r[0].t <= 1))
			return (r[0].t);
		return ((r[0].t = 0));
	}
	if (c == 'E')
	{
		r[0].wallpos[0] = set_wall_pos(rp[0].x, rp[0].y + 1);
		r[0].wallpos[1] = set_wall_pos(rp[0].x + 1, rp[0].y + 1);
		if (calc_t(r, map) > 0 && (r[0].t <= 1))
			return (r[0].t);
		return ((r[0].t = 0));
	}
	r[0].wallpos[0] = set_wall_pos(rp[0].x + ceilf(op), rp[0].y);
	r[0].wallpos[1] = set_wall_pos(rp[0].x + ceilf(op), rp[0].y + 1);
	if (calc_t(r, map) > 0 && (r[0].t <= 1))
		return (r[0].t);
	return ((r[0].t = 0));
}

double check_for_wall(t_ray *r, t_cub *map, char c)
{
	if (c == 'N' || c == 'S')
	{
		if (map->map[(int)r[0].pos[1].x][(int)r[0].pos[0].y] == '1')
			if (set_wall_north_south(r, map, c) != 0)
				return (r[0].t);
		if (map->map[(int)r[0].pos[0].x][(int)r[0].pos[1].y] == '1')
			if (set_wall_north_south(r, map, 0) != 0)
				return (r[0].t);
	}
	if (c == 'E' || c == 'W')
	{
		if (map->map[(int)r[0].pos[0].x][(int)r[0].pos[1].y] == '1')
			if (set_wall_east_west(r, map, c) != 0)
				return (r[0].t);
		if (map->map[(int)r[0].pos[1].x][(int)r[0].pos[0].y] == '1')
			if (set_wall_east_west(r, map, 0) != 0)
				return (r[0].t);
	}
	return (0);
}

check_for_sprite(t_ray r,t_cub *map,char c)
{
	dprintf(1,"tutut\n");
}

t_ray check_wall_north_south(t_ray r, t_cub *map, int j, char c)
{
	while (map->map[(int)r.pos[0].x][(int)r.pos[0].y] != '1')
	{
		r.pos[1] = set_ray_pos(r.pos[0].x + j, r.pos[0].y + r.tan.oppose);
		if ((int)r.pos[1].y != (int)r.pos[0].y)
			if (check_for_wall(&r, map, c) != 0)
				break;
		if (map->map[(int)r.pos[0].x][(int)r.pos[0].y] == '2')
			check_for_sprite(r, map, c);
		r.pos[0] = set_ray_pos(r.pos[1].x, r.pos[1].y);
	}
	if (r.t == 0)
	{
		r.pos[0] = set_ray_pos(r.pos[1].x - j, r.pos[1].y);
		set_wall_north_south(&r, map, c);
		if (r.t == 0)
		{
			r.pos[0] = set_ray_pos(r.pos[1].x, (r.pos[1].y + calc_del(r)));
			set_wall_north_south(&r, map, 0);
		}
	}
	return (r);
}

t_ray check_wall_east_west(t_ray r, t_cub *map, int j, char c)
{
	while (map->map[(int)r.pos[0].x][(int)r.pos[0].y] != '1')
	{
		r.pos[1] = set_ray_pos(r.pos[0].x + r.tan.oppose, r.pos[0].y + j);
		if ((int)r.pos[1].x != (int)r.pos[0].x)
		{
			if (check_for_wall(&r, map, c) != 0)
				break;
		}
		if (map->map[(int)r.pos[0].x][(int)r.pos[0].y] == '2')
			check_for_sprite(r, map, c);
		r.pos[0] = set_ray_pos(r.pos[1].x, r.pos[1].y);
	}
	if (r.t == 0)
	{
		r.pos[0] = set_ray_pos(r.pos[1].x + calc_del(r), r.pos[1].y);
		set_wall_east_west(&r, map, 0);
		if (r.t == 0)
		{
			r.pos[0] = set_ray_pos(r.pos[1].x, r.pos[1].y - j);
			set_wall_east_west(&r, map, c);
		}
	}
	return (r);
}

int check_wall_dist(t_cub *map, int i)
{
	t_float p[5];
	const double projdist = (map->screen.x / 2) / tanf((30 * (PI / 180)));
	p[1] = map->ray[i].wallpos[0];
	p[2] = map->ray[i].wallpos[1];
	p[3] = map->player.pos;
	map->ray[i].pointpos.x = p[1].x + (map->ray[i].t * (p[2].x - p[1].x));
	map->ray[i].pointpos.y = p[1].y + (map->ray[i].t * (p[2].y - p[1].y));
	p[4] = map->ray[i].pointpos;
	map->ray[i].walldist = sqrt(((p[4].x - p[3].x) * (p[4].x - p[3].x) +
								 ((p[4].y - p[3].y) * (p[4].y - p[3].y))));
	map->ray[i].wheight = (0.5 / map->ray[i].walldist) * projdist;
}

int check_wall_pos(t_cub *map, int i)
{
	const double angle = map->ray[i].tan.angle;

	map->ray[i].pos[0] = map->player.pos;
	map->ray[i].pos[1] = map->player.pos;
	if (angle >= 0 && angle < 45 || angle >= 315 && angle < 360)
		map->ray[i] = check_wall_north_south(map->ray[i], map, -1, 'N');
	if (angle >= 45 && angle < 135)
		map->ray[i] = check_wall_east_west(map->ray[i], map, 1, 'E');
	if (angle >= 135 && angle < 225)
		map->ray[i] = check_wall_north_south(map->ray[i], map, 1, 'S');
	if (angle >= 225 && angle < 315)
		map->ray[i] = check_wall_east_west(map->ray[i], map, -1, 'W');
	return (0);
}

void draw_raytab(t_cub *map, double diffangle)
{
	int i;
	double k;

	i = 0;
	k = 0;
	while ((k += diffangle) < 360)
		i++;
	map->tabsize = i;
	map->raytab = malloc(sizeof(t_raytab) * (i + 1));
	i++;
	while (i-- > 0 && (k -= diffangle) >= 0)
		map->raytab[i].angle = k;
	map->raytab[0].angle = 0;
	i = 0;
	k = 0;
	while (i < map->tabsize - 1 && map->raytab[i + 1].angle > 0)
	{
		if (map->raytab[i].angle >= 45 && map->raytab[i - 1].angle < 45 ||
			map->raytab[i].angle >= 135 && map->raytab[i - 1].angle < 135 ||
			map->raytab[i].angle >= 225 && map->raytab[i - 1].angle < 225 ||
			map->raytab[i].angle >= 315 && map->raytab[i - 1].angle < 315)
			k += 2;
		map->raytab[i].k = k;
		map->raytab[i].oppose = tan((map->raytab[i].angle - (k * 45)) * (PI / 180));
		if (map->raytab[i].angle > 135 && map->raytab[i].angle < 315)
			map->raytab[i].oppose *= -1;
		i++;
	}
}

void draw_base_ray(t_cub *map)
{
	int i;
	int start;

	i = 0;
	while (i < map->tabsize && map->raytab[i].angle <= map->player.orientation)
		i++;
	start = i - (map->screen.x / 2) - 1;
	if (start < 0)
		start += map->tabsize;
	i = 0;
	while (i < map->screen.x)
	{
		map->ray[i].tan = map->raytab[start];
		check_wall_pos(map, i);
		check_wall_dist(map, i);
		if (map->kp == 114)
		{
			dprintf(1, "Wh=%f\tWd=%f\tt=%f\ti=%d\n", map->ray[i].wallpos[0].x, map->ray[i].wallpos[0].y, map->ray[i].wheight, i);
			//dprintf(1,"Wh=%f\tWd=%f\tt=%f\ti=%d\n",map->ray[i].wallpos[1].x,map->ray[i].wallpos[1].y,map->ray[i].wheight,i);
		}
		start++;
		if (start == map->tabsize)
			start = 0;
		i++;
	}
}

int raytracing(t_cub *map)
{
	double angle;
	map->player.pos.x = map->player.pos_base.x + 0.5;
	map->player.pos.y = map->player.pos_base.y + 0.5;
	angle = (FOV / (double)map->screen.x);
	map->player.orientation = set_player_orientation(map, 0);
	draw_raytab(map, angle);
	//draw_base_ray(map);
	return (0);
}

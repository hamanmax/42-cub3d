/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:39:04 by mhaman            #+#    #+#             */
/*   Updated: 2020/09/30 08:35:25 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_int.h"

void print_backround(t_cub *map)
{
	int i;
	int j;

	i = 0;
	while (i < ((map->screen.x) * (map->screen.y)))
	{
		map->mlx.data[i] = map->colorsky;
		if (i >= (map->screen.x * map->screen.y) / 2)
			map->mlx.data[i] = map->colorfloor;
		i++;
	}
}

void print_front(t_cub *map)
{
	int i;
	int j;
	int k;
	int l;

	l = 0;
	i = 0;
	j = (map->screen.y - (int)map->ray[i].wheight) / 2;
	if (j < 0)
		j = 0;
	k = j + (int)map->ray[i].wheight;
	if (k > map->screen.y)
		k = map->screen.y - 1;
	while (i < map->screen.x)
	{
		while (l <= (int)map->ray[i].wheight && j <= k)
		{
			map->mlx.data[j * map->screen.x + i] = map->ray[i].color[l];
			l++;
			j++;
		}
		l = 0;
		free(map->ray[i].color);
		i++;
		if (i < map->screen.x)
		{
			j = (map->screen.y - (int)map->ray[i].wheight) / 2;
			if (j < 0)
				j = 0;
			k = j + (int)map->ray[i].wheight;
			if (k > map->screen.y)
				k = map->screen.y - 1;
		}
	}
}

void set_player_dir(t_cub *map, double angle)
{
	map->player_dir.x = -1 * cos(angle*(PI/180)) * 0.1;
	map->player_dir.y = sin(angle*(PI/180)) * 0.1;
}

void  move_forward(t_cub *map)
{
	if (map->kp == 119)
	{
		set_player_dir(map,map->player_orientation);
		map->player_pos.x += map->player_dir.x;
		map->player_pos.y += map->player_dir.y;
		if (map->map[(int)map->player_pos.x][(int)map->player_pos.y] == '1')
		{
		map->player_pos.x -= map->player_dir.x;
		map->player_pos.y -= map->player_dir.y;
		}
	}
	if (map->kp == 115)
	{
		set_player_dir(map,map->player_orientation);
		map->player_pos.x -= map->player_dir.x;
		map->player_pos.y -= map->player_dir.y;
		if (map->map[(int)map->player_pos.x][(int)map->player_pos.y] == '1')
		{
		map->player_pos.x += map->player_dir.x;
		map->player_pos.y += map->player_dir.y;
		}
	}
	if (map->kp == 97)
	{
		set_player_dir(map,map->player_orientation - 90);
		map->player_pos.x += map->player_dir.x;
		map->player_pos.y += map->player_dir.y;
		if (map->map[(int)map->player_pos.x][(int)map->player_pos.y] == '1')
		{
		map->player_pos.x -= map->player_dir.x + 0.01;
		map->player_pos.y -= map->player_dir.y + 0.01;
		}
	}
	if (map->kp == 100)
	{
		set_player_dir(map,map->player_orientation - 90);
		map->player_pos.x -= map->player_dir.x;
		map->player_pos.y -= map->player_dir.y;
		if (map->map[(int)map->player_pos.x][(int)map->player_pos.y] == '1')
		{
		map->player_pos.x += map->player_dir.x *2;
		map->player_pos.y += map->player_dir.y *2;
		}
	}
	if (map->kp == 101)
	{
		map->player_orientation += 1;
		if (map->player_orientation >= 360)
		map->player_orientation = 0;
	}
	if (map->kp == 113)
	{
		map->player_orientation -= 1;
		if (map->player_orientation <= 0)
		map->player_orientation = 360;
	}
}

int deal_key(int key, void *params)
{
	t_cub *map;

	map = params;
	dprintf(1,"%d\n", key);
	if (key == 119)
	{
		map->kp = key;
		return (1);
	}
	if (key == 115)
	{
		map->kp = key;
		return (1);
	}
	if (key == 100)
	{
		map->kp = 100;
	}
	if (key == 97)
	{
		map->kp = 97;
	}
	if (key == 101)
	{
		map->kp = 101;
	}
	if (key == 113)
	{
		map->kp = 113;
	}
	if (key == 32)
	{
		map->kp = 0;
	}
	return (0);
}

int main_loop(t_cub *map)
{
	map->c++;
	mlx_key_hook(map->mlx.ptr,deal_key,map);
	dprintf(1,"Test1\n");
	move_forward(map);
	dprintf(1,"Test2\n");
	ft_bzero(map->ray,sizeof(t_ray)* map->screen.x - 1);
	dprintf(1,"Test3\n");
	draw_base_ray(map);
	dprintf(1,"Test4\n");
	get_wall_lenght(map);
	dprintf(1,"Test5\n");
	print_backround(map);
	dprintf(1,"Test6\n");
	print_front(map);
	dprintf(1,"Test7\n");
	mlx_put_image_to_window(map->mlx.ptr, map->mlx.win, map->mlx.img, 0, 0);
	dprintf(1,"Test8\n");
	if (map->c == 1000)
	exit(1);
}

void create_new_black_window(t_cub *map)
{
	map->mlx.win = mlx_new_window(map->mlx.ptr, map->screen.x, map->screen.y, "Cub3d");
	map->mlx.img = mlx_new_image(map->mlx.ptr, map->screen.x, map->screen.y);
	map->mlx.data = (int *)mlx_get_data_addr(map->mlx.img, &map->mlx.bpp, &map->mlx.line_size, &map->mlx.endian);
	mlx_loop_hook(map->mlx.ptr, &main_loop,map);
	mlx_key_hook(map->mlx.win, deal_key, map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:39:04 by mhaman            #+#    #+#             */
/*   Updated: 2020/09/08 14:31:15 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_int.h"


void 	print_backround(t_cub *map)
{
	int i;
	int j;

	i = 0;
	while(i < ((map->screen.x) * (map->screen.y)))
	{
			map->mlx.data[i] = map->colorsky;
		if (i >= (map->screen.x * map->screen.y)/ 2)
			map->mlx.data[i] = map->colorfloor;
		i++;
	}
}

void	print_front(t_cub *map)
{
	int i;
	int j;
	int k;
	i = 0;
	j = (map->screen.y - (int)map->colonne[i].wallheight) / 2;
	k = j + (int)map->colonne[i].wallheight;
	while(i < map->screen.x)
	{
		map->mlx.data[j * map->screen.x + i] = 0;
		while (j++ < k)
			map->mlx.data[j * map->screen.x + i] = 16762880;
		map->mlx.data[(j) * map->screen.x + i] = 0;
		i++;
		j = (map->screen.y - (int)map->colonne[i].wallheight) / 2;
		k = j + (int)map->colonne[i].wallheight;
	}
}

void	move_forward(t_cub *map)
{
	int size_line;
	int endian;
	int bpp[2];	

	map->player_pos.x += 0.3;
	draw_ray(map,map->projection_id.x,map->projection_id.y);
	calc_correct_wallheight(map, map->projection_id.x,map->projection_id.y);
	calc_colonne_wallheight(map, map->projection_id.x,map->projection_id.y);
	map->mlx.data = (int *)mlx_get_data_addr(map->mlx.img2,bpp,&size_line,&endian);
	print_backround(map);
	print_front(map);
	mlx_destroy_image(map->mlx.ptr,map->mlx.img);
	mlx_put_image_to_window(map->mlx.ptr,map->mlx.win,map->mlx.img2,0,0);

}

int deal_key(int key,void *params)
{
	t_cub *map;
	
	map = params;
	printf("%d\n",key);
	if (key == 119)
	{		
		mlx_destroy_image(map->mlx.ptr,map->mlx.img);
		//move_forward(map);
		return(1);
	}
	return(0);
}



void create_new_black_window(t_cub *map)
{
	int size_line;
	int endian;
	int bpp[2];	
	
	
	map->mlx.ptr = mlx_init();
	map->mlx.win = mlx_new_window(map->mlx.ptr, map->screen.x, map->screen.y,"Test N1");
	map->mlx.img = mlx_new_image(map->mlx.ptr,map->screen.x,map->screen.y);
	map->mlx.data = (int *)mlx_get_data_addr(map->mlx.img,bpp,&size_line,&endian);
	print_backround(map);
	print_front(map);
	mlx_put_image_to_window(map->mlx.ptr,map->mlx.win,map->mlx.img,0,0);
	mlx_key_hook(map->mlx.win,deal_key,map);
	mlx_loop(map->mlx.ptr);
}

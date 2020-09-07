/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:39:04 by mhaman            #+#    #+#             */
/*   Updated: 2020/09/04 15:11:04 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_int.h"

void	move_forward(t_cub *map)
{
	int i = 0;
	
	while (i++ <= 10)
	{
	mlx_pixel_put(map->mlx.mlx_ptr,map->mlx.win_ptr,map->screen.x/2 + i,map->screen.y/2,0);
		i++;
	}
	map->player_pos.x += 2;
		draw_ray(map,map->projection_id.x,map->projection_id.y);
}

void	put_front2(t_cub *map)
{
	int j;

	j = 0;
	while (j <= map->screen.x)
	{
		mlx_pixel_put(map->mlx.mlx_ptr,map->mlx.win_ptr,j,(map->screen.y/2 - map->colonne[j].wallheight /2),0);
		mlx_pixel_put(map->mlx.mlx_ptr,map->mlx.win_ptr,j,(map->screen.y/2 + map->colonne[j].wallheight /2),0);

		j++;
	}
}



void	put_front(t_cub *map)
{
	size_t i;
	size_t j;
	size_t k;
	size_t l;
	size_t m;

	k = 0;
	l = 0;
	m = 0;
	i = map->projection_id.x;
	j = 0;
	while (j+k <= map->screen.x)
	{		
		if (map->ray[i].pointpos.y != map->ray[i - 1].pointpos.y &&
		map->ray[i].pointpos.x != map->ray[i - 1].pointpos.x)
		{
			while (m <= map->colonne[j+k].wallheight)
			{
				mlx_pixel_put(map->mlx.mlx_ptr,map->mlx.win_ptr,j +k,(map->screen.y/2 - map->colonne[j+k].wallheight /2) + m,0);
				m++;
			}
			j++;
			m = 1;
		}
		while(j < map->screen.x/60)
		{
			while(l < map->colonne[j+k].wallheight)
			{
				if (map->ray[i].pointpos.y == (int)map->ray[i].pointpos.y)
					mlx_pixel_put(map->mlx.mlx_ptr,map->mlx.win_ptr,j+k,(map->screen.y/2 - map->colonne[j+k].wallheight /2) + l,16743680);
				else
					mlx_pixel_put(map->mlx.mlx_ptr,map->mlx.win_ptr,j+k,(map->screen.y/2 - map->colonne[j+k].wallheight /2) + l,16762880);
				l++;
			}
			mlx_pixel_put(map->mlx.mlx_ptr,map->mlx.win_ptr,j+k,map->screen.y/2 - map->colonne[j+k].wallheight /2,0);
			mlx_pixel_put(map->mlx.mlx_ptr,map->mlx.win_ptr,j+k,map->screen.y/2 + map->colonne[j+k].wallheight/2,0);
			l = 0;
			j++;
		}
		if (j == map->screen.x/60)
		{
			k += j;
			j = 0;
			i++;
		}
	}

}

int deal_key(int key,void *params)
{
	t_cub *map;
	void *win_ptr2;
	
	map = params;
	printf("%d\n",key);
	if (key == 119)
	{		
		return(1);
	}
	return(0);
}

void put_backround(t_cub *map)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (j <= map->screen.y/2)
	{
		mlx_pixel_put(map->mlx.mlx_ptr,map->mlx.win_ptr,i,j,map->colorsky);
		mlx_pixel_put(map->mlx.mlx_ptr,map->mlx.win_ptr,i,j + map->screen.y/2,map->colorfloor);
		i++;
		if (i == map->screen.x)
		{
			i = 0;
			j++;
		}
	}

}

void create_new_black_window(t_cub *map)
{
	unsigned int xpm1_x;
	int xpm1_y;
	int size_line;
	int endian;
	int bpp[2];	
	unsigned int tutu;
	void *img_ptr;
	void *img_ptr2;
	char *data = ft_strdup("");
	int i = 15;
	int j = 0;
	
	
	map->mlx.mlx_ptr = mlx_init();
	map->mlx.win_ptr = mlx_new_window(map->mlx.mlx_ptr, map->screen.x, map->screen.y,"Test N1");
	img_ptr = mlx_new_image(map->mlx.mlx_ptr,map->screen.x,map->screen.y);
	//img_ptr2 = mlx_xpm_file_to_image(map->mlx.mlx_ptr,"mur.xpm",&xpm1_x,&xpm1_y);
	put_backround(map);
	put_front(map);
	//mlx_put_image_to_window(map->mlx.mlx_ptr,map->mlx.win_ptr,img_ptr2,50,50);
	//printf("tftftft\n");
	mlx_key_hook(map->mlx.win_ptr,deal_key,map);
	data = ft_strdup(mlx_get_data_addr(img_ptr,bpp,&size_line,&endian));
	xpm1_x = mlx_get_color_value(map->mlx.mlx_ptr,map->colorfloor);
	printf("%d\t%d\n",bpp[1],xpm1_x);
	mlx_loop(map->mlx.mlx_ptr);
}

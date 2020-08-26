/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:39:04 by mhaman            #+#    #+#             */
/*   Updated: 2020/08/26 11:16:56 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_int.h"

int rgb_calc(t_cub *map)
{
	int rgb;

}

int deal_key(int key,void *params)
{
	printf("%d\n",key);
	
	return(0);
}

void put_front(void *mlx_ptr,void *win_ptr,t_cub *map,t_ray *ray)
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
	while (i <= map->projection_id.y)
	{		
		if (ray[i].pointpos.x != ray[i - 1].pointpos.x && ray[i].pointpos.y != ray[i - 1].pointpos.y)
		{
			while (m < ray[i].wallheight)
			{
				mlx_pixel_put(mlx_ptr,win_ptr,j +k,(map->screen.y/2 - ray[i].wallheight /2) + m,0);
				m++;
			}
			m = 1;
			j++;
		}
		while(j < map->screen.x/60)
		{
			while(l < ray[i].wallheight)
			{
				mlx_pixel_put(mlx_ptr,win_ptr,j+k,(map->screen.y/2 - ray[i].wallheight /2) + l,16762880);
				if (ray[i].pointpos.y == (int)ray[i].pointpos.y)
				{
					mlx_pixel_put(mlx_ptr,win_ptr,j+k,(map->screen.y/2 - ray[i].wallheight /2) + l,16743680);
				}
				l++;
			}
			mlx_pixel_put(mlx_ptr,win_ptr,j+k,map->screen.y/2 - ray[i].wallheight /2,0);
			mlx_pixel_put(mlx_ptr,win_ptr,j+k,map->screen.y/2 + ray[i].wallheight/2,0);

			l = 0;
			j++;
		}
		if (ray[i].pointpos.x != ray[i + 1].pointpos.x && ray[i].pointpos.y != ray[i + 1].pointpos.y)
		{
			while (m < ray[i].wallheight)
			{
				mlx_pixel_put(mlx_ptr,win_ptr,j +k,(map->screen.y/2 - ray[i].wallheight /2) + m,0);
				m++;
			}
			m = 1;
		}
		if (j == map->screen.x/60)
		{
			k += j;
			j = 0;
			i++;
		}
	}

}


void put_backround(void *mlx_ptr,void *win_ptr,t_cub *map)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (j <= map->screen.y/2)
	{
		mlx_pixel_put(mlx_ptr,win_ptr,i,j,map->colorsky);
		mlx_pixel_put(mlx_ptr,win_ptr,i,j + map->screen.y/2,map->colorfloor);
		i++;
		if (i == map->screen.x)
		{
			i = 0;
			j++;
		}
	}

}

void create_new_black_window(t_cub *map,t_ray *ray)
{
	void *mlx_ptr;
	void *win_ptr;
	int xpm1_x;
	int xpm1_y;
	unsigned int tutu;
	void *img_ptr;
	void *img_ptr2;
	int i = 15;
	int j = 0;
	void *p;
	
  //  p = mlx;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, map->screen.x, map->screen.y,"Test N1");
	//img_ptr2 = mlx_xpm_file_to_image(mlx_ptr,"mur.xpm",&xpm1_x,&xpm1_y);
	put_backround(mlx_ptr,win_ptr,map);
	put_front(mlx_ptr,win_ptr,map,ray);
	//mlx_put_image_to_window(mlx_ptr,win_ptr,img_ptr2,50,50);
   	mlx_key_hook(win_ptr,deal_key,(void*)0);
	mlx_loop(mlx_ptr);
	rgb_calc(map);
}

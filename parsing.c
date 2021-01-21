/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 09:53:46 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 16:22:06 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int		parse_file_cub(t_cub *map, char **argv, int argc)
{
	int		fd;
	char	*line;
	char	rbuff[300 + 1];
	int		rsize;

	fd = open(argv[1], O_RDONLY);
	line = ft_strdup("");
	while (1)
	{
		rsize = read(fd, rbuff, 300);
		if (rsize == -1)
			break ;
		rbuff[rsize] = 0;
		line = ft_strfjoin(line, rbuff, 1);
		if (rsize != 300)
			break ;
	}
	check_file_validity(map, argv, argc);
	check_instruction_validity(map, &line);
	check_struct_validity(map, 1);
	close(fd);
	return (0);
}

int		check_around_char(char **tab, size_t x, size_t y, char *tofind)
{
	size_t	d;
	char	buffer[256];

	d = 0;
	ft_memset(buffer, 0, 256);
	while (tofind[d])
		buffer[tofind[d++]] = 1;
	if (buffer[tab[x + 1][y]] != 1 || buffer[tab[x - 1][y]] != 1)
		return (0);
	else if (buffer[tab[x][y + 1]] != 1 || buffer[tab[x][y - 1]] != 1)
		return (0);
	else if (buffer[tab[x - 1][y - 1]] != 1 || buffer[tab[x + 1][y + 1]] != 1)
		return (0);
	else if (buffer[tab[x - 1][y + 1]] != 1 || buffer[tab[x + 1][y - 1]] != 1)
		return (0);
	return (1);
}

void	resizing_map(t_cub *map)
{
	if (map->screen.x > 1920 || map->screen.y > 1080)
	{
		printf("Resizing to display resolution\n");
		map->screen.x = 1920;
		map->screen.y = 1080;
	}
	if ((map->screen.x >= 0 && map->screen.x < 200) ||
	(map->screen.y >= 0 && map->screen.y < 200))
	{
		printf("Resizing up screen resolution\n");
		map->screen.x = 640;
		map->screen.y = 480;
	}
}

int		error_str_return(char *str)
{
	ft_printf("ERROR\n%s\n", str);
	exit(-1);
}

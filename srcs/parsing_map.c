/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:59:58 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 20:56:33 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		check_map_validity(t_cub *map, char *found, char **line)
{
	const int	j = (ft_str_char_occur(*line, '\n') + 1);
	int			i;
	char		*buff;

	i = 1;
	*line = ft_strfjoin("\n", *line, 4);
	*line = ft_strfjoin(found, *line, 2);
	map->map = malloc((j + 3) * sizeof(char *));
	buff = *line;
	while ((found = ft_strsep(line, "\n")) && i <= j + 1)
		if (found[0] == '1' || found[0] == ' ')
			map->map[i++] = ft_strdup(found);
		else
			error_str_return("Bad map parsing\n");
	free(buff);
	*line = NULL;
	if (i == j + 1)
		error_str_return("Information / Line after map");
	map->mapsize.y = i - 1;
	test_map_validity(map, i - 1);
	return (0);
}

int		test_map_validity(t_cub *map, int nbline)
{
	int			i;
	int			j;

	i = 1;
	j = 0;
	while (map->map[i][j] == ' ' || map->map[i][j] == '1')
	{
		j++;
		if (map->map[i][j] == 0 && i != nbline)
		{
			i = nbline;
			j = 0;
		}
	}
	if (map->map[i][j] != 0)
		error_str_return("Map not valid");
	i = 1;
	while (i <= nbline - 1 && (map->map[i][ft_strlen(map->map[i]) - 1] == ' ' ||
	map->map[i][ft_strlen(map->map[i]) - 1] == '1'))
		i++;
	if (i != nbline)
		error_str_return("Map not valid");
	return (test_map_integrity(map, nbline));
}

int		test_map_integrity(t_cub *map, int nbline)
{
	char		buffer[256];
	const char	str[9] = "012 NSEW";
	int			i;

	i = 0;
	ft_memset(buffer, 0, 256);
	while (str[i])
		buffer[str[i++]] = 1;
	while (str[i - 4])
		buffer[str[i++ - 4]] = 2;
	test_map_char_integrity(map, nbline, buffer, 1);
	test_map_overall_integrity(map, nbline);
	return (1);
}

void	test_map_char_integrity(t_cub *map, int nbline, char b[256], int j)
{
	while (nbline >= 1)
	{
		if (map->map[nbline][j] && b[map->map[nbline][j]] != 1)
		{
			if (b[map->map[nbline][j]] == 0 ||
			(b[map->map[nbline][j]] == 2 && map->pla.pos.y != 0))
				error_str_return("Bad Map Integriy");
			else if (b[map->map[nbline][j]] == 2)
			{
				map->pla.pos.x = (double)nbline;
				map->pla.pos.y = (double)j + 1;
			}
		}
		if (b[map->map[nbline][j]] == 1 && map->map[nbline][j] == '2')
			map->nbsprite++;
		if (map->map[nbline][j] == 0)
		{
			nbline--;
			j = 0;
		}
		j++;
	}
	if (map->pla.pos.y == 0 || map->pla.pos.x == 0)
		error_str_return("Player pos not set");
}

int		test_map_overall_integrity(t_cub *map, int nbline)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (++i <= nbline)
		if (ft_strlen(map->map[i]) >= j)
			j = ft_strlen(map->map[i]) + 2;
	map->map[i] = ft_str_malloc(j, ' ');
	map->map[0] = ft_str_malloc(j, ' ');
	map->mapsize.x = j - 1;
	while (--i > 0)
	{
		map->map[i] = ft_strfjoin(" ", map->map[i], 2);
		map->map[i] = ft_strfjoin(map->map[i],
		ft_str_malloc(j - ft_strlen(map->map[i]), ' '), 3);
	}
	i = 1;
	j = 1;
	check_around_map(map, i, j, nbline);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 09:53:46 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/19 18:52:42 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_file_cub(t_cub *map, char **argv, int argc)
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

int	check_instruction_validity(t_cub *map, char **line)
{
	char		*found;
	const char	*top = *line;

	while ((*line && (found = ft_strsep(line, "\n"))))
	{
		if (found[0])
		{
			if (ft_strnstr(found, "R ", 3))
				check_resolution_validity(map, found);
			else if (ft_strnstr(found, "C ", 3))
				check_color_validity(map, found, map->colorsky);
			else if (ft_strnstr(found, "F ", 3))
				check_color_validity(map, found, map->colorfloor);
			else if (check_type_texture(found) != -1)
				check_texture_validity(map, found);
			else if (ft_strnstr(found, "1", 1) || ft_strnstr(found, " ", 1))
				check_map_validity(map, found, line);
			else
				error_str_return("Unreconized Arguments");
		}
	}
	free((char *)top);
	return (1);
}

int	check_texture_validity(t_cub *map, char *line)
{
	char		*found;
	char		*texture[3];
	size_t		i;

	i = 0;
	if (map->text[check_type_texture(line)])
		error_str_return("Textures Indication given twice");
	while ((found = ft_strsep(&line, " ")) && i <= 2)
		if (found[0])
			texture[i++] = found;
	if (i < 2 || i > 2)
		error_str_return("Too many/not enought information");
	map->text[check_type_texture(texture[0])] = ft_strdup(texture[1]);
	if ((i = open(map->text[check_type_texture(texture[0])], O_RDONLY)) == -1)
		error_str_return("can't open texture files");
	close(i);
	return (1);
}

int	check_type_texture(char *line)
{
	if (ft_strnstr(line, "NO", 2))
		return (0);
	else if (ft_strnstr(line, "SO", 2))
		return (1);
	else if (ft_strnstr(line, "WE", 2))
		return (2);
	else if (ft_strnstr(line, "EA", 2))
		return (3);
	else if (ft_strnstr(line, "S", 1))
		return (4);
	return (-1);
}

int	check_map_validity(t_cub *map, char *found, char **line)
{
	const int		j = (ft_str_char_occur(*line,'\n') + 1);
	int		i;
	char	*buff;

	i = 1;
	*line = ft_strfjoin(" ",*line, 4);
	*line = ft_strfjoin(found,*line,2);
	(*line)[ft_strlen(found)] = '\n';
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
	check_struct_validity(map, 0);
	test_map_validity(map, i - 1);
}

int	test_map_validity(t_cub *map,int nbline)
{
	int				i;
	int				j;
	
	i = 1;
	j = 0;
	while(map->map[i][j] == ' ' || map->map[i][j] == '1')
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
	while(i <= nbline - 1 && (map->map[i][ft_strlen(map->map[i]) - 1] == ' ' ||
	map->map[i][ft_strlen(map->map[i]) - 1] == '1'))
		i++;
	if (i != nbline)
		error_str_return("Map not valid2");
	return (test_map_integrity(map, nbline));
}

int	test_map_integrity(t_cub *map, int nbline)
{
	char buffer[256];
	const char str[9] = "012 NSEW";
	int cardpt;
	int i;
	int j;

	cardpt = 0;
	i = 0;
	j = 0;
	ft_memset(buffer, 0, 256);
	while(str[i])
		buffer[str[i++]] = 1;
	while(str[i - 4])
		buffer[str[i++ - 4]] = 2;
	i = 0;
	test_map_char_integrity(map, nbline, buffer, 1);
	test_map_overall_integrity(map, nbline);
	return (1);
}

int	test_map_char_integrity(t_cub *map,int nbline, char buffer[256],int j)
{
	while (nbline >= 1)
	{
		if (map->map[nbline][j] && buffer[map->map[nbline][j]] != 1)
		{
			if (buffer[map->map[nbline][j]] == 0 ||
			(buffer[map->map[nbline][j]] == 2 && map->player_pos.y != 0))
				exit(printf("ERROR\nProblem at line %d column %d",nbline + 1,j));
			else if (buffer[map->map[nbline][j]] == 2)
			{
				map->player_pos.x = nbline;
				map->player_pos.y = j;
			}
		}
		if (map->map[nbline][j] == 0)
		{
			nbline--;
			j = 0;
		}
		j++;
	}
	if (map->player_pos.y == 0 || map->player_pos.x == 0)
		error_str_return("Player pos not set");
}


int	test_map_overall_integrity(t_cub *map, int nbline)
{
	int		i;
	size_t	j;

	i = 0;
	j = 1;
	while (++i <= nbline)
		if (ft_strlen(map->map[i]) >= j)
			j = ft_strlen(map->map[i]) + 2;
	map->map[i] = ft_str_malloc(j, ' ');
	map->map[0] = ft_str_malloc(j, ' ');
	while (--i > 0)
	{
		map->map[i] = ft_strfjoin(" ", map->map[i], 2);
		map->map[i] = ft_strfjoin(map->map[i], ft_str_malloc(j - ft_strlen(map->map[i]), ' '), 5);
		printf("%s\n",map->map[i]);
	}
	i = 1;
	j = 1;
	while (i < nbline)
	{
		if (!map->map[i][j] && i++)
			j = 1;
		if (map->map[i][j+1] != 0 && map->map[i][j] == ' ' && j != ft_strlen(map->map[i]))
			if (check_around_char(map->map,i,j,"1 ") == 0)
				error_str_return("Map not close");
		j++;
	}
}

int	check_around_char(char **tab, size_t x, size_t y, char *tofind)
{
	size_t d;
	char buffer[256];

	d = 0;
	ft_memset(buffer, 0, 256);
	while(tofind[d])
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

int	check_struct_validity(t_cub *map,size_t i)
{
	if (!map->screen.x || !map->screen.y)
		error_str_return("Resolution not set");
	if (!map->colorfloor[0])
		error_str_return("Color Floor not set");
	if (!map->colorsky[0])
		error_str_return("Color sky not set");
	if (!map->text[NO])
		error_str_return("NORTH texture not set");
	if (!map->text[SO])
		error_str_return("SOUTH texture not set");
	if (!map->text[WE])
		error_str_return("WEST texture not set");
	if (!map->text[EA])
		error_str_return("EAST texture not set");
	if (!map->text[SPRITE])
		error_str_return("SPRITE texture not set");
	if (i == 1 && !map->map)
		error_str_return("Map description not set");
	return (0);
}

int	check_color_validity(t_cub *map, char *line, int color[4])
{
	char		*found;
	int			i;

	i = 0;
	if (color[0])
		error_str_return("Multiple times Color sky instruction");
	if (ft_str_char_occur(line,',') != 2)
		error_str_return("to much/not enought ',' in instruction");
	color[0] = line[0];
	while ((found = ft_strsep(&line, " ,")) && i != 5)
		if (found[0] != 0)
		{
			color[++i] = ft_atoi(found);
			if (color[i] < 0 || color[i] > 255)
				error_str_return("Color Must be between 0 and 255");
			if (ft_str_isdigit(found) == 0 && i > 1)
				error_str_return("Color must be digits");
		}
	if (i > 4 || i < 4)
		error_str_return("Too many/not enought arguments, color need 4");
	return (1);
}

int	check_resolution_validity(t_cub *map, char *line)
{
	char		*found;
	size_t		i;

	i = 0;
	if (map->screen.x != 0 || map->screen.y != 0)
		error_str_return("Multiple times Resolution instruction");
	while ((found = ft_strsep(&line, " ")) && i != 5)
	{
		if (found[0] != 0 && i == 1)
			map->screen.x = ft_atoi(found);
		else if (found[0] != 0 && i == 2)
			map->screen.y = ft_atoi(found);
		if (found[0] != 0)
			i++;
		if (ft_str_isdigit(found) == 0 && i > 1 && i < 4)
			error_str_return("Resolution must be digits");
	}
	if (i > 3)
		error_str_return("Too many arguments, resolution need 3 got more");
	if (i < 3)
		error_str_return("Not enought arguments, resolution need 3 got less");
	resizing_map(map);
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
		map->screen.y = 360;
	}
}

int	check_file_validity(t_cub *map, char **argv, int argc)
{
	int			fd;
	char		*file;

	if (argc < 2)
		error_str_return("Missing map file");
	if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 8) != 0)
			error_str_return("Bad option here only --save available");
	if ((file = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) == NULL)
		error_str_return("No .cub format found");
	else
	{
		file -= 1;
		if (*file == 0)
			error_str_return("File need name");
		file += 5;
		if (*file != 0)
			error_str_return("Bad Format File");
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error_str_return("Could not open file");
	else
		close(fd);
	return (1);
}

int ft_str_char_occur(char *str, int c)
{
	size_t i;

	i = 0;
	while(*str)
	{
		if(*str == c)
			i++;
		str++;
	}
	return(i);
}

int	ft_str_isdigit(char *str)
{
	size_t		i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == 0)
		return (1);
	return (0);
}

int	error_str_return(char *str)
{
	printf("ERROR\n%s", str);
	exit(-1);
}

int	main(int argc, char **argv)
{
	char		buff[1024];
	t_cub		*map;

	ft_bzero((map = malloc(sizeof(t_cub))), sizeof(t_cub));
	parse_file_cub(map, argv, argc);
	printf("file valid\n");
	free(map->text[0]);
	free(map->text[1]);
	free(map->text[2]);
	free(map->text[3]);
	free(map->text[4]);
	free(map->map[0]);
	free(map->map[1]);
	free(map->map[2]);
	free(map->map[3]);
	free(map->map[4]);
	free(map->map[5]);
	free(map->map[6]);
	free(map->map[7]);
	free(map->map[8]);
	free(map->map[9]);
	free(map->map[10]);
	free(map->map[11]);
	free(map->map[12]);
	free(map->map[13]);
	free(map->map[14]);
	free(map->map[15]);
	free(map->map);
	free(map);
	return (0);
}

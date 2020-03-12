/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhama     n@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 09:53:46 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/12 14:07:36 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "libft/libft.h"

enum			e_text
{
	NO,
	SO,
	WE,
	EA,
	SPRITE,
	TEXTURE_COUNT
};

typedef	struct	s_float
{
	double	x;
	double	y;
}				t_float;

typedef	struct	s_int
{
	int		x;
	int		y;
}				t_int;

typedef struct	s_cub
{
	int screenlength;
	int screenwidth;
	int colorsky[4];
	int colorfloor[4];
	int northtexture;
	int southtexture;
	int easttexture;
	int westtexture;
	int spritetexture;
	char **map;
	t_int	player_pos;
	char *text[TEXTURE_COUNT];
}				t_cub;

int parse_file_cub(t_cub *map, char **argv, int argc)
{
	int fd;
	char *line;
	check_file_validity(map,argv, argc);
	check_instruction_validity(map,argv);
return(0);
}

int	check_instruction_validity(t_cub *map, char ** argv)
{
	int fd;
	char *line;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) != 0)
	{
		if (line[0] != 0)
		{
			if (ft_strnstr(line,"R ",3) != NULL)
			{
				check_resolution_validity(map, line);
			}
			else if (ft_strnstr(line,"C ",3) != NULL)
			{
				check_sky_validity(map, line);
			}
			else if (ft_strnstr(line,"F ",3) != NULL)
			{
				check_floor_validity(map, line);
			}
			else if (ft_strnstr(line,"S ",3) || ft_strnstr(line,"SO ",4)
			|| ft_strnstr(line,"NO ",4) || ft_strnstr(line,"WE ",4)
			|| ft_strnstr(line,"EA ",4))
			{
				check_texture_validity(map, line);
			}
			else if (ft_strnstr(line,"1 ",3) || ft_strnstr(line,"  ",3))
			{
				check_map_validity(map, line);
			}
			else
			{
				free(line);
				error_str_return("Unreconized Arguments");
			}
			free(line);
		}
	}
}

int check_texture_validity(t_cub *map, char *line)
{
	char *found;
	char *texture[2];
	size_t i;

	i = 0;
	if ((ft_strnstr(line,"S ",3) && map->text[SPRITE]) ||
	(ft_strnstr(line,"SO ",4) && map->text[SO]) || (ft_strnstr(line,"NO ",4)
	&& map->text[NO]) || (ft_strnstr(line,"WE ",4) && map->text[WE]) ||
	(ft_strnstr(line,"EA ",4) && map->text[EA]))
		error_str_return("Textures Indication given twice");
	while ((found = ft_strsep(&line," ")))
		if (found[0])
			texture[i++] = found;
	if (i < 2 || i > 2)
		error_str_return("Too many/not enought information");
	map->text[check_type_texture(texture[0])] = ft_strdup(texture[1]);
	if ((i = open(map->text[check_type_texture(texture[0])],O_RDONLY)) == -1)
		error_str_return("can't open texture files");
	else
		close(i);
}

int	check_type_texture(char *line)
{
	if (ft_strnstr(line,"NO",3))
		return(0);
	else if (ft_strnstr(line,"SO",3))
		return(1);
	else if (ft_strnstr(line,"WE",3))
		return(2);
	else if (ft_strnstr(line,"EA",3))
		return(3);
	return(4);
}

int check_map_validity(t_cub *map, char *line)
{
	check_struct_validity(map);
}

int	check_struct_validity(t_cub *map)
{
	if (!map->screenlength || !map->screenwidth)
		error_str_return("Resolution not set");
	if (!map->colorfloor[0])
		error_str_return("Color Sky not set");
	if (!map->colorsky[0])
		error_str_return("Color Floor not set");
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

}

int check_floor_validity(t_cub *map, char *line)
{
	char *found;
	char *colorfloor[5];
	size_t i;

	i = 0;
	if (map->colorfloor[0] != 0 && map->colorfloor[1] != 0 &&
	map->colorfloor[2] != 0)
		error_str_return("Multiple times Color floor instruction");
	while ((found = ft_strsep(&line," ,")) &&  i != 5)
		if (found[0] != 0)
		{
			colorfloor[i++] = found;
			printf("%s\n",colorfloor[i - 1]);
		}
	if (i > 4)
		error_str_return("Too many arguments, colorfloor need 3 got more ");
	if (i < 4)
		error_str_return("Not enought arguments, colorfloor need 3 got less ");
	while (--i >= 1)
		map->colorfloor[i - 1] = ft_atoi(colorfloor[i]);
	map->colorfloor[0] = colorfloor[0][0];
	if (map->colorfloor[0] < 0 || map->colorfloor[0] > 255 ||
	map->colorfloor[1] < 0 || map->colorfloor[1] > 255 ||
	map->colorfloor[2] < 0 || map->colorfloor[2] > 255)
		error_str_return("Color floor Must be between 0 and 255");
	return (1);
}

int check_sky_validity(t_cub *map, char *line)
{
	char *found;
	char *colorsky[5];
	size_t i;

	i = 0;
	if (map->colorsky[0] != 0 && map->colorsky[1] != 0 &&
	map->colorsky[2] != 0)
		error_str_return("Multiple times Color sky instruction");
	while ((found = ft_strsep(&line," ,")) != NULL &&  i != 5)
		if (found[0] != 0)
		{
			colorsky[i++] = found;
		}
	if (i > 4)
		error_str_return("Too many arguments, colorsky need 3 got more ");
	if (i < 4)
		error_str_return("Not enought arguments, colorsky need 3 got less ");
	while (--i >= 1)
		map->colorsky[i - 1] = ft_atoi(colorsky[i]);
	if (map->colorsky[0] < 0 || map->colorsky[0] > 255 ||
	map->colorsky[1] < 0 || map->colorsky[1] > 255 ||
	map->colorsky[2] < 0 || map->colorsky[2] > 255)
		error_str_return("Color sky Must be between 0 and 255");
	return (1);
}

int check_resolution_validity(t_cub *map, char *line)
{
	char *found;
	char *resolution[4];
	size_t i;

	i = 0;
	if (map->screenlength != 0 || map->screenwidth != 0)
		error_str_return("Multiple times Resolution instruction");
	while ((found = ft_strsep(&line," ")) != NULL &&  i != 4)
		if (found[0] != 0)
			resolution[i++] = found;
	if (i > 3)
		error_str_return("Too many arguments, resolution need 3 got more ");
	if (i < 3)
		error_str_return("Not enought arguments, resolution need 3 got less ");
	map->screenlength = ft_atoi(resolution[1]);
	map->screenwidth = ft_atoi(resolution[2]);
	if (map->screenwidth <= 0 || map->screenlength <= 0)
		error_str_return("Resolution width or length can't be 0 or negativ");
	if (map->screenwidth > 3840 || map->screenlength > 2160)
	{
		printf("Resizing screen resolution\n");
		map->screenlength = 3840;
		map->screenwidth = 2160;
	}
}

int	check_file_validity(t_cub *map,char **argv,int argc)
{
	int fd;
	char *file;

	if (argc < 2)
		error_str_return("Missing map file");
	if(argc == 3)
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
	if ((fd = open(argv[1],O_RDONLY)) == -1)
		error_str_return("Could not open file");
	else
		close(fd);
	return (1);
}

int error_str_return(char *str)
{
	printf("ERROR\n%s", str);
	exit(-1);
}

int main(int argc, char** argv)
{
	char *line;
	char	buff[1024];

	t_cub *map;
	ft_bzero((map = malloc(sizeof(t_cub))), sizeof(t_cub));
	parse_file_cub(map, argv, argc);
	printf("file valid\n");
	free(map);
	return (0);
}
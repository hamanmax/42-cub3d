/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 07:02:47 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/08 17:40:58 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	free_str(char **ptr, int ret)
{
	free(*ptr);
	return (ret);
}

size_t	next_newline(char **line, char **rest, size_t rsize)
{
	size_t	lsize;
	char	*temp;

	if ((ft_strchr(*rest, '\n') == NULL))
	{
		lsize = ft_strlen(*rest);
		if (!(*line = ft_substr(*rest, 0, lsize)))
			return (free_str(rest, -1));
		free(*rest);
		*rest = NULL;
		return (0);
	}
	temp = ft_strchr(*rest, '\n');
	*temp = '\0';
	lsize = ft_strlen(*rest);
	if (!(*line = ft_substr(*rest, 0, lsize)))
		return (free_str(rest, -1));
	if (!(temp = ft_substr(*rest, lsize + 1, rsize)))
		return (free_str(rest, -1));
	free(*rest);
	if (!(*rest = ft_strdup(temp)))
		return (free_str(rest, -1));
	free(temp);
	return (1);
}

size_t	next_read(char **rest, int fd, char **line, size_t rsize)
{
	size_t	esize;
	char	buffer2[100 + 1];

	while (!(ft_strchr(*rest, '\n')))
	{
		esize = read(fd, buffer2, 100);
		buffer2[esize] = '\0';
		rsize += esize;
		if (!(*rest = ft_strjoin(*rest, buffer2)))
			return (free_str(rest, -1));
		if (esize != 100)
			break ;
	}
	return (next_newline(line, rest, rsize));
}

int		get_next_line(int fd, char **line)
{
	char			buffer[100 + 1];
	static	char	*rest = NULL;
	size_t			rsize;

	*line = NULL;
	if (!line || 100 < 1 || read(fd, buffer, 0) < 0)
	{
		*line = ft_strdup("");
		return (free_str(&rest, -1));
	}
	if (!rest)
		if (!(rest = ft_strdup("")))
			return (free_str(&rest, -1));
	rsize = 100;
	if (ft_strchr(rest, '\n'))
		return (next_newline(line, &rest, rsize));
	return (next_read(&rest, fd, line, rsize));
}

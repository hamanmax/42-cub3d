/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 08:29:59 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/11 10:40:17 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*ft_strjoin(char *str1, const char *str2)
{
	char			*joinstr;
	const	size_t	lenstr1 = ft_strlen(str1);
	const	size_t	lenstr2 = ft_strlen(str2);
	size_t			i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	if (!(joinstr = malloc((lenstr1 + lenstr2) + 1)))
		return (0);
	while (i < lenstr1)
		if ((joinstr[i] = str1[i]))
			i++;
	while (i < (lenstr2 + lenstr1))
		if ((joinstr[i] = str2[i - lenstr1]))
			i++;
	joinstr[i] = '\0';
	free(str1);
	return (joinstr);
}

char	*ft_strdup(char *str)
{
	char			*ptr;
	int				i;
	int				k;

	k = 0;
	i = 0;
	while (str[i])
		i++;
	if (!(ptr = malloc((i + 1) * sizeof(char))))
		return (0);
	while (str[k])
	{
		ptr[k] = str[k];
		k++;
	}
	ptr[k] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (c != (char)*str)
			str++;
		else
			return ((char*)str);
	}
	if (c == '\0' && *str == '\0')
		return ((char*)str);
	else
		return (NULL);
}

char	*ft_substr(char *str, unsigned int start, size_t len)
{
	char			*finalstr;
	size_t			i;

	i = 0;
	if (!(finalstr = malloc((sizeof(char) * len + 1))))
		return (0);
	while (len > i && str[start])
	{
		finalstr[i] = str[start];
		i++;
		start++;
	}
	finalstr[i] = '\0';
	return (finalstr);
}

size_t	ft_strlen(const char *str)
{
	int				i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

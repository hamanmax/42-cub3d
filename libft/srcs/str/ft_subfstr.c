/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subfstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:06:39 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 12:43:19 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	ft_strnlen(const char *s, unsigned int len)
{
	size_t i;

	i = 0;
	while (len > i && s[i])
		i++;
	return (i);
}

extern	char	*ft_subfstr(char *s, unsigned int start, size_t len)
{
	char		*s2;
	size_t		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strnlen(s, start) && *s)
		return (ft_strdup(""));
	if (!(s2 = ft_calloc((len + 1), sizeof(char))))
		return (NULL);
	while (len > i && *s)
	{
		s2[i] = s[start];
		i++;
		start++;
	}
	s2[i] = '\0';
	free(s);
	return (s2);
}

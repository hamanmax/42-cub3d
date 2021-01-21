/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:36:22 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 12:43:19 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static	size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t i;

	i = 0;
	while (i < maxlen && s[i])
		i++;
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	const size_t lendst = ft_strnlen(dst, size);
	const size_t lensrc = ft_strlen(src);

	if (lendst != size)
	{
		if (lensrc >= size - lendst)
		{
			ft_memcpy(dst + lendst, src, size - lendst - 1);
			dst[size - 1] = '\0';
		}
		else
			ft_memcpy(dst + lendst, src, lensrc + 1);
	}
	return (lendst + lensrc);
}

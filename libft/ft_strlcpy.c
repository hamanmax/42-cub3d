/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 10:00:37 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/04 09:40:26 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t lensrc;

	lensrc = ft_strlen(src);
	if (lensrc + 1 < size)
		ft_memcpy(dst, src, (lensrc + 1));
	else if (size != 0)
	{
		ft_memcpy(dst, src, (size - 1));
		dst[size - 1] = '\0';
	}
	return (lensrc);
}

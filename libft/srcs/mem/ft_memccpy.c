/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:09:38 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 12:43:19 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int		i;
	int		j;
	char	*d;
	char	*s;

	i = 0;
	j = 0;
	s = (char*)src;
	d = (char*)dst;
	while (n > 0 && s[j])
	{
		d[i] = s[j];
		i++;
		j++;
		n--;
		if (s[i - 1] == (char)c)
			return (dst + i);
	}
	return (NULL);
}

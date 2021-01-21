/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:42:38 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 12:43:19 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char *ts;

	ts = (char*)s;
	while (n > 0)
	{
		if (c != *ts)
		{
			ts++;
			n--;
		}
		else
			return (ts);
	}
	return (0);
}

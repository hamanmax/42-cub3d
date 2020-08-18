/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:25:02 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/04 09:42:14 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n > 0 && *(char*)s1 == *(char*)s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n > 0)
		return (*(unsigned char*)s1 - *(unsigned char*)s2);
	return (0);
}

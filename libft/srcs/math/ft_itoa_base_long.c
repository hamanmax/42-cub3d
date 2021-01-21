/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:24:16 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 12:43:19 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_itoa_base_long(unsigned long nbr, char *base)
{
	size_t			lbase;
	size_t			k;
	static char		str[18] = {0};

	k = 16;
	lbase = ft_strlen(base);
	while (1)
	{
		str[--k] = base[nbr % lbase];
		nbr /= lbase;
		if (nbr == 0)
			break ;
	}
	return (ft_strdup(str + k));
}

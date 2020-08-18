/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:24:16 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/04 09:40:26 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

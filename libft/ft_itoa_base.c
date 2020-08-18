/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:02:05 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/04 09:40:26 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa_base(unsigned int nbr, char *base)
{
	size_t			lbase;
	size_t			k;
	static char		str[18] = {0};
	unsigned long	nb;

	k = 14;
	nb = nbr;
	lbase = ft_strlen(base);
	while (1)
	{
		str[--k] = base[nb % lbase];
		nb /= lbase;
		if (nb == 0)
			break ;
	}
	return (ft_strdup(str + k));
}

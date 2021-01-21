/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 09:47:12 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 12:43:19 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static	int		ft_lenint(long n)
{
	int		nb;
	int		k;

	nb = n;
	k = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / 10;
		k++;
	}
	return (k);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		k;
	int		negativ;
	long	nbr;

	nbr = (int)n;
	negativ = 0;
	if (nbr < 0)
	{
		nbr = nbr * -1;
		negativ = 1;
		k = ft_lenint(nbr) + 1;
	}
	else
		k = ft_lenint(nbr);
	if (!(str = ft_calloc((k) + 1, sizeof(char))))
		return (NULL);
	while (k-- > 0)
	{
		str[k] = (nbr % 10) + '0';
		nbr = nbr / 10;
		if (negativ == 1 && k == 0)
			str[k] = '-';
	}
	return (str);
}

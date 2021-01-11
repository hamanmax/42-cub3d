/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:59:08 by mhaman            #+#    #+#             */
/*   Updated: 2020/10/19 14:01:34 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power > 1)
	{
		power--;
		return (nb * ft_pow(nb, power));
	}
	return (nb);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:01:13 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 17:10:21 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

double	ft_round(double nb, int round)
{
	int			trunct;
	const	int	pow = ft_pow(10, round);

	nb *= pow;
	trunct = (int)nb;
	nb = (double)trunct / pow;
	return (nb);
}

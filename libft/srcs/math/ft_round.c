/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:01:13 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 16:53:58 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "stdio.h"

double ft_round(double nb,int round)
{
	int trunct;
	const int pow = ft_pow(10,round);
	nb *= pow;
	ft_printf("%.20f\n",nb);
	trunct = (int)nb;
	ft_printf("%d\n",trunct);
	nb = (double)trunct / pow;
	ft_printf("%.20f\n",nb);
	return(nb);
}
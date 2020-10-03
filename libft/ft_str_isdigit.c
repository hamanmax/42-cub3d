/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 22:02:07 by aviscogl          #+#    #+#             */
/*   Updated: 2020/10/02 22:02:07 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_isdigit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == 0)
		return (1);
	return (0);
}
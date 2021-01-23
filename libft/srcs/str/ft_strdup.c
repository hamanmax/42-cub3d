/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:23:53 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/23 12:02:39 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (s1[i])
		i++;
	ptr = ft_xmalloc((i + 1) * sizeof(char));
	while (s1[k])
	{
		ptr[k] = s1[k];
		k++;
	}
	ptr[k] = '\0';
	return (ptr);
}

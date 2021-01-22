/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:06:39 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 17:17:47 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*finalstr;
	size_t			i;

	i = 0;
	if (!(finalstr = malloc((sizeof(char) * len + 1))))
		return (0);
	while (len > i && s[start])
	{
		finalstr[i] = s[start];
		i++;
		start++;
	}
	finalstr[i] = '\0';
	return (finalstr);
}

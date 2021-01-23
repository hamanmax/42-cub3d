/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:06:39 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/23 12:02:35 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*finalstr;
	size_t			i;

	i = 0;
	finalstr = ft_xmalloc((sizeof(char) * len + 1));
	while (len > i && s[start])
	{
		finalstr[i] = s[start];
		i++;
		start++;
	}
	finalstr[i] = '\0';
	return (finalstr);
}

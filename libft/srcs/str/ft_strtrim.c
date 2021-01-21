/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:06:59 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 12:43:19 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			start;
	size_t			end;
	unsigned char	buffer[256];

	ft_memset(buffer, 0, 256 * sizeof(unsigned char));
	while (*set)
	{
		buffer[(unsigned char)*set] = 1;
		set++;
	}
	start = 0;
	while (buffer[(unsigned char)s1[start]] == 1)
		start++;
	if (s1[start] == '\0')
		return (ft_calloc(1, 1));
	end = ft_strlen(s1) - 1;
	while (buffer[(unsigned char)s1[end]] == 1)
		end--;
	return (ft_substr((char *)s1, start, end - start + 1));
}

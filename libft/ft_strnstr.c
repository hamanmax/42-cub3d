/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 07:06:30 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/04 09:40:26 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char*)haystack + i - j);
	while (haystack[i] != needle[j] && haystack[i] && len > i)
		i++;
	while (haystack[i] == needle[j] && haystack[i] != '\0' && len > i)
	{
		i++;
		j++;
		if (needle[j] == '\0')
			return ((char*)haystack + i - j);
		if (haystack[i] != needle[j])
		{
			i = i - j + 1;
			j = 0;
			while (haystack[i] != needle[j] && len > i && haystack[i])
				i++;
		}
	}
	return (NULL);
}

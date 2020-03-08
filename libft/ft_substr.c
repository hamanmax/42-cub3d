/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:06:39 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/08 17:35:48 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

extern	char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*s2;
	size_t		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (!(s2 = ft_calloc((len + 1), sizeof(char))))
		return (0);
	while (len > i && s[start])
	{
		s2[i] = s[start];
		i++;
		start++;
	}
	s2[i] = '\0';
	return (s2);
}

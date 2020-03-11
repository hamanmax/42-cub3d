/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:06:39 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/11 10:44:43 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// extern	char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char		*s2;
// 	size_t		i;

// 	if (s == NULL)
// 		return (NULL);
// 	i = 0;
// 	if (!(s2 = malloc((sizeof(char) * len + 1))))
// 		return (0);
// 	while (len > i && s[start])
// 	{
// 		s2[i] = s[start];
// 		i++;
// 		start++;
// 	}
// 	s2[i] = '\0';
// 	return (s2);
// }

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
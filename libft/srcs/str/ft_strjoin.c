/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:58:29 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 12:43:19 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char			*s3;
// 	const size_t	lens1 = ft_strlen(s1);
// 	const size_t	lens2 = ft_strlen(s2);

// 	if (!(s3 = (char*)malloc((lens1 + lens2) + 1)))
// 		return (0);
// 	ft_memcpy(s3, s1, lens1);
// 	ft_memcpy(s3 + lens1, s2, lens2);
// 	s3[lens2 + lens1] = '\0';
// 	return (s3);
// }

char	*ft_strjoin(char const *s1, const char *s2)
{
	char			*joinstr;
	const	size_t	lenstr1 = ft_strlen(s1);
	const	size_t	lenstr2 = ft_strlen(s2);
	size_t			i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (!(joinstr = malloc((lenstr1 + lenstr2) + 1)))
		return (0);
	while (i < lenstr1)
		if ((joinstr[i] = s1[i]))
			i++;
	while (i < (lenstr2 + lenstr1))
		if ((joinstr[i] = s2[i - lenstr1]))
			i++;
	joinstr[i] = '\0';
	free((char *)s1);
	return (joinstr);
}

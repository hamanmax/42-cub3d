/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:58:29 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/04 09:40:26 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*s3;
	const size_t	lens1 = ft_strlen(s1);
	const size_t	lens2 = ft_strlen(s2);

	if (!(s3 = (char*)malloc((lens1 + lens2) + 1)))
		return (0);
	ft_memcpy(s3, s1, lens1);
	ft_memcpy(s3 + lens1, s2, lens2);
	s3[lens2 + lens1] = '\0';
	return (s3);
}

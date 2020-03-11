/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:04:09 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/11 15:16:45 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (c != (char)*str)
			str++;
		else
		{
			return ((char*)str);
		}
	}
	if (c == '\0' && *str == '\0')
		return ((char*)str);
	else
		return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:37:10 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/11 16:48:35 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strsep(char **stringp, const char *delim)
{
	char	*old_pointer;

	old_pointer = *stringp;
	if (!old_pointer || **stringp == 0)
		return (NULL);
	if (old_pointer)
	{
		if ((**stringp) && ft_strchr(delim, (**stringp)))
		{
			(**stringp) = 0;
			(*stringp)++;
			return (old_pointer);
		}
		while ((*stringp) && !ft_strchr(delim, (**stringp)))
		{
			(*stringp)++;
		}
		if (**stringp != 0)
		{
			**stringp = 0;
			(*stringp)++;
		}
	}
	return (old_pointer);
}

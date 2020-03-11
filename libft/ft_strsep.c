/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:37:10 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/11 06:32:35 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strsep(char **stringp, const char *delim)
{
	size_t	i;
	char	*tok;

	i = 0;
	if (*stringp == NULL || **stringp == 0)
		return (NULL);
	tok = *stringp;
	while (**stringp && **stringp != delim[i])
	{
		while (delim[i] && **stringp != delim[i])
			i++;
		if (**stringp != delim[i])
			i = 0;
		else
			break ;
		(*stringp)++;
	}
	if (**stringp == delim[i])
		**stringp = 0;
	(*stringp)++;
	return (tok);
}

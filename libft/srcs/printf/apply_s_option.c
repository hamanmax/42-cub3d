/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_s_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:58:23 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 17:14:44 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftprintf.h"
#include "../include/libft.h"

int		apply_s_option(char **str, va_list ap, size_t i, size_t j)
{
	char	*arg;
	size_t	neg;

	neg = 0;
	if (str[i][0] == '-')
	{
		neg = 1;
		str[i][0] = ' ';
	}
	while (str[i][j] == ' ' || str[i][j] == '0' || str[i][j] == '-')
		j++;
	if (!(arg = apply_point_flag_s(str, ap, i, j)))
		return (-1);
	if (j >= ft_strlen(arg))
	{
		if (!(str[i] = ft_subfstr(str[i], 0, j - ft_strlen(arg))))
			return (free_strp(arg, NULL, NULL, 1));
	}
	else
		str[i][0] = 0;
	if ((str[i] = ft_strfjoin(str[i], arg, 3)) == NULL)
		return (free_strp(arg, NULL, NULL, 1));
	return (apply_minus_flag(str, i, 0, neg));
}

char	*apply_point_flag_s(char **str, va_list ap, size_t i, size_t j)
{
	char	*arg;
	char	*temp;
	size_t	nbr;

	nbr = 0;
	if (str[i][j] == '.')
		nbr = 1;
	temp = va_arg(ap, char *);
	if (temp)
		temp = ft_strdup(temp);
	if (temp == NULL)
		if (!(temp = ft_strfdup("(null)", temp)))
			return (NULL);
	if (!(arg = ft_strdup(temp)))
		return (free_strp_typestr(temp, NULL, NULL, 1));
	nbr = (size_t)ft_atoi(str[i] + j + nbr);
	if (nbr < ft_strlen(arg) && str[i][j] == '.')
	{
		if (!(arg = ft_subfstr(arg, 0, nbr)))
			return (free_strp_typestr(arg, temp, NULL, 4));
	}
	free(temp);
	return (arg);
}

int		check_multiflag_pourcent(char **str, size_t i, size_t j)
{
	while (str[i][j] == '0')
		j++;
	if (str[i][j] == '-')
	{
		while (str[i][j] == '0' || str[i][j] == '-')
			j++;
		if (str[i][j])
		{
			if ((str[i] = ft_subfstr(str[i], j, ft_strlen(str[i]) - j)) == NULL)
				return (-1);
			if ((str[i] = ft_strfjoin("-", str[i], 2)) == NULL)
				return (-1);
		}
	}
	return (1);
}

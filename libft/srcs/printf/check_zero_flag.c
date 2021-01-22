/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_zero_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:18:41 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 17:14:51 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftprintf.h"
#include "../include/libft.h"

int		check_zero_flag(char **str, size_t i, size_t j)
{
	while (str[i][j] && str[i][j] != '.')
		j++;
	if (str[i][j] == 0)
	{
		if (apply_zero_flag(str, '0', i, 0) == -1)
			return (-1);
	}
	else
	{
		if ((apply_zero_flag(str, ' ', i, 0)) == -1)
			return (-1);
	}
	return (1);
}

int		check_zero_flag_pourcent(char **str, size_t i, size_t j)
{
	if (str[i][j] == '0')
	{
		if (apply_zero_flag(str, '0', i, j) == -1)
			return (-1);
	}
	else
	{
		if ((apply_zero_flag(str, ' ', i, j)) == -1)
			return (-1);
	}
	return (1);
}

int		apply_c_option_bis(char **str, size_t i, va_list ap)
{
	if (!(str[i] = ft_subfstr(str[i], 0, ft_strlen(str[i]) - 2)))
		return (-1);
	ft_putstr_fd(str[i], 1);
	ft_putchar_fd(va_arg(ap, int), 1);
	return (1);
}

size_t	apply_d_option_neg(char **str, size_t i)
{
	str[i][0] = ' ';
	return (1);
}

char	*apply_point_flag_bis(size_t nbr, size_t d, char *arg)
{
	char	*temp;

	if (!(temp = ft_str_malloc((nbr + d - ft_strlen(arg)), '0')))
		return (free_strp_typestr(arg, NULL, NULL, 1));
	if (arg[0] == '-')
	{
		temp[0] = '-';
		arg[0] = '0';
	}
	if (!(arg = ft_strfjoin(temp, arg, 3)))
		return (free_strp_typestr(arg, temp, NULL, 4));
	return (arg);
}

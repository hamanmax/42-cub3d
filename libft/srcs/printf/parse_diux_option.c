/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_diux_option.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 08:07:19 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 17:15:02 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftprintf.h"
#include "../include/libft.h"

int	parse_u_option(char **str, va_list ap, size_t i, size_t j)
{
	if (apply_stars_flag(str, ap, i, 0) == -1)
		return (-1);
	if (str[i][j] >= '1' && str[i][j] <= '9')
	{
		if (apply_zero_flag(str, ' ', i, 0) == -1)
			return (-1);
	}
	else if (str[i][j] == '0')
	{
		if (check_zero_flag(str, i, j) == -1)
			return (-1);
	}
	else if (str[i][0] == '-')
	{
		if ((apply_zero_flag(str, ' ', i, 1)) == -1)
			return (-1);
		str[i][0] = '-';
	}
	return (apply_u_option(str, ap, i, 0));
}

int	parse_ux_option(char **str, va_list ap, size_t i, size_t j)
{
	if (apply_stars_flag(str, ap, i, 0) == -1)
		return (-1);
	if (str[i][j] >= '1' && str[i][j] <= '9')
	{
		if (apply_zero_flag(str, ' ', i, 0) == -1)
			return (-1);
	}
	else if (str[i][j] == '0')
	{
		if (check_zero_flag(str, i, j) == -1)
			return (-1);
	}
	else if (str[i][0] == '-')
	{
		if (apply_zero_flag(str, ' ', i, 1) == -1)
			return (-1);
		str[i][0] = '-';
	}
	return (apply_ux_option(str, ap, i, 0));
}

int	parse_x_option(char **str, va_list ap, size_t i, size_t j)
{
	if (apply_stars_flag(str, ap, i, 0) == -1)
		j = 0;
	if (str[i][j] >= '1' && str[i][j] <= '9')
	{
		if (apply_zero_flag(str, ' ', i, 0) == -1)
			return (-1);
	}
	else if (str[i][0] == '0')
	{
		if (check_zero_flag(str, i, 0) == -1)
			return (-1);
	}
	else if (str[i][0] == '-')
	{
		if (apply_zero_flag(str, ' ', i, 1) == -1)
			return (-1);
		str[i][0] = '-';
	}
	return (apply_x_option(str, ap, i, 0));
}

int	parse_d_option(char **str, va_list ap, size_t i, size_t j)
{
	if (apply_stars_flag(str, ap, i, 0) == -1)
		return (-1);
	if (str[i][0] == '0' && str[i][1] == '-')
		j = 1;
	if (str[i][j] >= '1' && str[i][j] <= '9')
	{
		if (apply_zero_flag(str, ' ', i, 0) == -1)
			return (-1);
	}
	else if (str[i][j] == '0')
	{
		if (check_zero_flag(str, i, j) == -1)
			return (-1);
	}
	else if (str[i][j] == '-')
	{
		if (apply_zero_flag(str, ' ', i, 1) == -1)
			return (-1);
		str[i][0] = '-';
	}
	return (apply_d_option(str, ap, i, 0));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:15:33 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 17:15:23 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftprintf.h"
#include "../include/libft.h"

int	parsing_line(char **str, va_list ap, size_t i, size_t *len)
{
	size_t	j;

	j = 1;
	while (str[i][j] && str[i][0] == '%')
	{
		if (str[i][j] == 'i' || str[i][j] == 'd')
			return (parse_d_option(str, ap, i, 0));
		else if (str[i][j] == 'u')
			return (parse_u_option(str, ap, i, 0));
		else if (str[i][j] == 'x')
			return (parse_x_option(str, ap, i, 0));
		else if (str[i][j] == 'X')
			return (parse_ux_option(str, ap, i, 0));
		else if (str[i][j] == 'c')
			return (parse_c_option(str, ap, i, len));
		else if (str[i][j] == '%')
			return (parse_pourcent_option(str, ap, i, 0));
		else if (str[i][j] == 'p')
			return (parse_p_option(str, ap, i, 0));
		else if (str[i][j] == 's')
			return (parse_s_option(str, ap, i, 0));
		else
			j++;
	}
	return (1);
}

int	parse_c_option(char **str, va_list ap, size_t i, size_t *len)
{
	size_t j;

	j = 0;
	if (apply_stars_flag(str, ap, i, 0) == -1)
		return (-1);
	j = 0;
	if (str[i][j] >= '1' && str[i][j] <= '9')
	{
		if (apply_zero_flag(str, ' ', i, 0) == -1)
			return (-1);
	}
	else if (str[i][j] == '-')
	{
		if (apply_zero_flag(str, ' ', i, 1) == -1)
			return (-1);
		str[i][0] = '-';
	}
	return (apply_c_option(str, ap, i, len));
}

int	parse_pourcent_option(char **str, va_list ap, size_t i, size_t j)
{
	if (check_precision(str, i) == -1)
		return (-1);
	if (apply_stars_flag(str, ap, i, 0) == -1)
		return (-1);
	if (check_multiflag_pourcent(str, i, j) == -1)
		return (-1);
	if (str[i][0] >= '0' && str[i][0] <= '9')
	{
		if (check_zero_flag_pourcent(str, i, j) == -1)
			return (-1);
	}
	else if (str[i][0] == '-' && str[i][1] != '%')
	{
		if (apply_zero_flag(str, ' ', i, 0) == -1)
			return (-1);
		str[i][0] = '%';
		if (!(str[i] = ft_subfstr(str[i], 0, ft_strlen(str[i]) - 1)))
			return (-1);
	}
	if (str[i][0] == '0' || str[i][0] == ' ' || str[i][0] == '-')
		if (!(str[i] = ft_subfstr(str[i], 1, ft_strlen(str[i]) - 1)))
			return (-1);
	return (1);
}

int	parse_p_option(char **str, va_list ap, size_t i, size_t j)
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
			return (1);
		str[i][0] = '-';
	}
	return (apply_p_option(str, ap, i, 0));
}

int	parse_s_option(char **str, va_list ap, size_t i, size_t j)
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
	return (apply_s_option(str, ap, i, 0));
}

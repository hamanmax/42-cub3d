/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_d_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:14:01 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 17:14:37 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftprintf.h"
#include "../include/libft.h"

int		apply_d_option(char **str, va_list ap, size_t i, size_t j)
{
	char	*arg;
	size_t	neg;

	neg = 0;
	if (str[i][0] == '-')
		neg = apply_d_option_neg(str, i);
	while (str[i][j] == ' ' || str[i][j] == '0' || str[i][j] == '-')
		j++;
	if ((arg = apply_point_flag(str, ap, i, j)) == NULL)
		return (-1);
	if (str[i][0] == '0' && arg[0] == '-' && j > ft_strlen(arg))
	{
		str[i][0] = '-';
		arg[0] = '0';
	}
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

int		apply_stars_flag(char **str, va_list ap, size_t i, size_t j)
{
	while (str[i][j] && str[i][j] != '*')
		j++;
	while (str[i][j])
	{
		if (str[i][j] == '*')
		{
			if (apply_stars_flag_bis(str, ap, i, j) == -1)
				return (-1);
		}
		if (str[i][j])
			j++;
	}
	if ((str[i] = ft_subfstr(str[i], 1, (ft_strlen(str[i]) - 1))) == NULL)
		return (-1);
	return (1);
}

char	*apply_point_flag(char **str, va_list ap, size_t i, size_t j)
{
	size_t	nbr;
	char	*arg;
	size_t	d;

	d = 0;
	nbr = ft_atoi(str[i] + j);
	if (str[i][j] == '.')
		nbr = ft_atoi(str[i] + j + 1);
	if (!(arg = ft_itoa(va_arg(ap, int))))
		return (NULL);
	if (arg[0] == '-')
		d = 1;
	if (str[i][j] == '.' && nbr == 0 && arg[0] == '0')
	{
		if (!(arg = ft_strfdup("", arg)))
			return (free_strp_typestr(arg, NULL, NULL, 1));
	}
	else if (nbr < 2147483648 && nbr >= ft_strlen(arg))
	{
		if (!(arg = apply_point_flag_bis(nbr, d, arg)))
			return (NULL);
	}
	return (arg);
}

int		apply_minus_flag(char **str, size_t i, size_t j, size_t neg)
{
	if (neg != 1)
		return (1);
	while (str[i][j] && str[i][j] == ' ')
		j++;
	if ((str[i] = ft_subfstr(str[i], j, ft_strlen(str[i]) - j)) == NULL)
		return (-1);
	if ((str[i] = ft_strfjoin(str[i], ft_str_malloc(j, ' '), 3)) == NULL)
		return (-1);
	return (1);
}

int		apply_zero_flag(char **str, char c, size_t i, size_t j)
{
	size_t	nbr;
	char	*temp;
	char	*arg;

	while (str[i][j] && (str[i][j] == ' ' || str[i][j] == '-'))
		j++;
	nbr = ft_atoi(str[i] + j);
	if (nbr > 2147483647)
		nbr = 0;
	while (str[i] && (str[i][j] >= '0' && str[i][j] <= '9'))
		j++;
	if ((temp = ft_str_malloc(nbr, c)) == NULL)
		return (-1);
	if ((arg = ft_subfstr(str[i], j, (ft_strlen(str[i]) - j))) == NULL)
		return (free_strp(temp, NULL, NULL, 1));
	if ((str[i] = ft_strfjoin(temp, arg, 3)) == NULL)
		return (free_strp(arg, temp, NULL, 4));
	return (1);
}

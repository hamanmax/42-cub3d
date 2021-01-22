/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_cu_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:14:01 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 17:13:38 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftprintf.h"
#include "../include/libft.h"

int		apply_u_option(char **str, va_list ap, size_t i, size_t j)
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
	if (!(arg = apply_point_flag_u(str, ap, i, j)))
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

char	*apply_point_flag_u(char **str, va_list ap, size_t i, size_t j)
{
	size_t	nbr;
	char	*arg;
	size_t	d;

	d = 0;
	nbr = ft_atoi(str[i] + j);
	if (str[i][j] == '.')
		nbr = ft_atoi(str[i] + j + 1);
	if (!(arg = ft_itoa_unsigned(va_arg(ap, unsigned int))))
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

int		apply_c_option(char **str, va_list ap, size_t i, size_t *len)
{
	if (str[i][0] == ' ')
	{
		if ((apply_c_option_bis(str, i, ap) == -1))
			return (-1);
	}
	else if (str[i][0] != '-' || str[i][1] == 0)
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		str[i][0] = 0;
	}
	else if (str[i][0] == '-')
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		if (str[i][1] != 0)
		{
			if (!(str[i] = ft_subfstr(str[i], 0, ft_strlen(str[i]) - 2)))
				return (-1);
			if (str[i][0] == '-')
				str[i][0] = ' ';
			ft_putstr_fd(str[i], 1);
		}
	}
	*len += ft_strlen(str[i]) + 1;
	str[i][0] = 0;
	return (1);
}

int		apply_p_option(char **str, va_list ap, size_t i, size_t j)
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
	if (!(arg = apply_point_flag_p(str, ap, i, j)))
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

char	*apply_point_flag_p(char **str, va_list ap, size_t i, size_t j)
{
	size_t	nbr;
	char	*arg;
	char	*temp;

	if ((nbr = ft_atoi(str[i] + j)) || str[i][j] == '.')
		nbr = ft_atoi(str[i] + j + 1);
	if (!(arg = ft_itoa_base_long(va_arg(ap, size_t), "0123456789abcdef")))
		return (free_strp_typestr(arg, NULL, NULL, 1));
	if (str[i][j] == '.' && arg[0] == '0')
		arg[0] = 0;
	if (!(arg = ft_strfjoin("0x", arg, 2)))
		return (NULL);
	else if (nbr >= ft_strlen(arg))
	{
		if (!(temp = ft_str_malloc((nbr - ft_strlen(arg)), '0')))
			return (free_strp_typestr(arg, NULL, NULL, 1));
		if (arg[0] == '-')
		{
			temp[0] = '-';
			arg[0] = '0';
		}
		if (!(arg = ft_strfjoin(temp, arg, 3)))
			return (free_strp_typestr(temp, arg, NULL, 4));
	}
	return (arg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:16:13 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 17:14:55 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftprintf.h"
#include "../include/libft.h"

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	char	**tabstr;
	size_t	d;
	size_t	i;
	size_t	len;

	len = 0;
	va_start(ap, format);
	d = 0;
	i = 0;
	if (format[0] == 0)
		return (0);
	if ((tabstr = ft_split_ft_printf(format, &d)) == NULL)
		return (-1);
	while (d > i)
	{
		if (parsing_line(tabstr, ap, i, &len) == -1)
			return (free_tab(tabstr, d));
		ft_putstr_fd(tabstr[i], 1);
		len += ft_strlen(tabstr[i]);
		i++;
	}
	free_tab(tabstr, d);
	i = 0;
	return (len);
}

int		free_tab(char **tabstr, size_t d)
{
	size_t i;

	i = 0;
	while (d > i)
	{
		free(tabstr[i]);
		i++;
	}
	free(tabstr);
	return (-1);
}

int		free_strp(char *s1, char *s2, char *s3, size_t i)
{
	if (i == 1)
		free(s1);
	else if (i == 2)
		free(s2);
	else if (i == 3)
		free(s3);
	else if (i == 4)
	{
		free(s1);
		free(s2);
	}
	else
	{
		free(s1);
		free(s2);
		free(s3);
	}
	return (-1);
}

char	*free_strp_typestr(char *s1, char *s2, char *s3, size_t i)
{
	if (i == 1)
		free(s1);
	else if (i == 2)
		free(s2);
	else if (i == 3)
		free(s3);
	else if (i == 4)
	{
		free(s1);
		free(s2);
	}
	else
	{
		free(s1);
		free(s2);
		free(s3);
	}
	return (NULL);
}

int		apply_stars_flag_bis(char **str, va_list ap, size_t i, size_t j)
{
	char			*temp;
	char			*arg;
	const int		nbr = va_arg(ap, int);

	if ((str[i][j - 1] == '.' && nbr < 0 && str[i][j + 1] == 'X') ||
	str[i][j + 1] == 'x')
	{
		if (!(str[i] = ft_subfstr(str[i], 0, j - 1)))
			return (-1);
		if (!(str[i] = ft_strfjoin(str[i], "X", 1)))
			return (-1);
		return (1);
	}
	if (str[i][j - 1] == '.' && nbr < 0 && str[i][j + 1] != 's')
		if (check_precision(str, i) == -1)
			return (-1);
	if ((arg = ft_itoa(nbr)) == NULL)
		return (-1);
	if (!(temp = ft_substr(str[i], j + 1, ft_strlen(str[i]) - (j + 1))))
		return (free_strp(arg, NULL, NULL, 1));
	if (!(str[i] = ft_strfjoin(ft_subfstr(str[i], 0, j), arg, 3)))
		return (free_strp(temp, arg, NULL, 4));
	if ((str[i] = ft_strfjoin(str[i], temp, 3)) == NULL)
		return (free_strp(temp, arg, NULL, 4));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 10:35:35 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 17:14:59 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ftprintf.h"
#include "../include/libft.h"

size_t		check_option(const char str)
{
	const	char	*option = "%csdiupxX";
	size_t			i;

	i = 0;
	while (option[i])
	{
		if (option[i] == str)
			return (1);
		else
			i++;
	}
	return (0);
}

char		*ft_str_malloc(int n, char c)
{
	char			*dest;

	if (!(dest = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	dest[n] = 0;
	ft_memset(dest, c, n);
	return (dest);
}

size_t		ft_strchrnbr(const char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (str[j] != '%')
		j++;
	while (str[i])
	{
		if (str[i] && str[i] == '%')
		{
			i++;
			while (str[i] && check_option(str[i]) == 0)
				i++;
			if (check_option(str[i]) == 1)
				j++;
			i++;
			if (str[i] && str[i] != '%')
				j++;
		}
		else
			i++;
	}
	return (j);
}

char		**ft_create_tab(const char *str, size_t i, size_t j, size_t len)
{
	char			**tab;
	const	size_t	index = ft_strchrnbr(str);

	if (!(tab = (char **)malloc((index + 1) * sizeof(char *))))
		return (NULL);
	while (j <= index && str[len + i])
	{
		if (str[len + i++] == '%')
		{
			while (check_option(str[len + i]) == 0)
				i++;
			i++;
		}
		else
			while (str[len + i] && str[len + i] != '%')
				i++;
		if ((tab[j] = ft_str_malloc(i, '#')) == NULL)
			free_tab(tab, j);
		if (tab[j] == NULL)
			return (NULL);
		j++;
		len += i;
		i = 0;
	}
	return (tab);
}

char		**ft_split_ft_printf(const char *str, size_t *d)
{
	char			**tab;
	const	size_t	index = ft_strchrnbr(str);
	size_t			i;
	size_t			j;
	size_t			k;

	i = 0;
	j = 0;
	k = 0;
	*d = ft_strchrnbr(str);
	if (!(tab = ft_create_tab(str, 0, 0, 0)))
		return (NULL);
	while (i < index)
	{
		while (tab[i] && tab[i][j] != '\0')
		{
			tab[i][j] = str[k];
			k++;
			j++;
		}
		j = 0;
		i++;
	}
	return (tab);
}

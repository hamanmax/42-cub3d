/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 10:05:10 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/24 11:00:57 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPRINTF_H
# define FTPRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include "./libft.h"

char	**ft_split_ft_printf(const char *str, size_t *d);
int		ft_ft_printf(const char *format, ...);
int		parsing_line(char **str, va_list ap, size_t i, size_t *len);
int		parse_d_option(char **str, va_list ap, size_t i, size_t j);
int		parse_u_option(char **str, va_list ap, size_t i, size_t j);
int		parse_x_option(char **str, va_list ap, size_t i, size_t j);
int		parse_ux_option(char **str, va_list ap, size_t i, size_t j);
int		parse_p_option(char **str, va_list ap, size_t i, size_t j);
int		parse_c_option(char **str, va_list ap, size_t i, size_t *len);
int		parse_pourcent_option(char **str, va_list ap, size_t i, size_t j);
int		parse_s_option(char **str, va_list ap, size_t i, size_t j);
int		apply_stars_flag(char **str, va_list ap, size_t i, size_t j);
int		apply_d_option(char **str, va_list ap, size_t i, size_t j);
int		apply_u_option(char **str, va_list ap, size_t i, size_t j);
int		apply_x_option(char **str, va_list ap, size_t i, size_t j);
int		apply_ux_option(char **str, va_list ap, size_t i, size_t j);
int		apply_p_option(char **str, va_list ap, size_t i, size_t j);
int		apply_c_option(char **str, va_list ap, size_t i, size_t *len);
int		apply_s_option(char **str, va_list ap, size_t i, size_t j);
int		apply_pourcent_option(char **str, size_t i, size_t j);
int		apply_zero_flag(char **str, char c, size_t i, size_t j);
int		apply_minus_flag(char **str, size_t i, size_t j, size_t neg);
char	*apply_point_flag(char **str, va_list ap, size_t i, size_t j);
char	*apply_point_flag_u(char **str, va_list ap, size_t i, size_t j);
char	*apply_point_flag_x(char **str, va_list ap, size_t i, size_t j);
char	*apply_point_flag_ux(char **str, va_list ap, size_t i, size_t j);
char	*apply_point_flag_p(char **str, va_list ap, size_t i, size_t j);
char	*apply_point_flag_s(char **str, va_list ap, size_t i, size_t j);
char	*ft_str_malloc(int n, char c);
int		check_precision(char **str, size_t i);
int		free_strp(char *s1, char *s2, char *s3, size_t i);
char	*free_strp_typestr(char *s1, char *s2, char *s3, size_t i);
int		free_tab(char **tabstr, size_t d);
int		check_zero_flag(char **str, size_t i, size_t j);
int		check_zero_flag_pourcent(char **str, size_t i, size_t j);
int		apply_c_option_bis(char **str, size_t i, va_list ap);
size_t	apply_d_option_neg(char **str, size_t i);
char	*apply_point_flag_bis(size_t nbr, size_t d, char *arg);
int		apply_stars_flag_bis(char **str, va_list ap, size_t i, size_t j);
int		check_multiflag_pourcent(char **str, size_t i, size_t j);
int		ft_printf(const char *format, ...);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:58:20 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 16:52:50 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "ftprintf.h"

int		ft_atoi(const char *str);
void	ft_bzero(void *b, size_t len);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
char	**ft_split(const	char *s, char c);
char	*ft_strchr(const char *str, int c);
char	*ft_strfdup(char *src, char *old);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strfjoin(char *s1, char *s2, int f);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *string, const char *to_find, size_t len);
char	*ft_strsep(char **stringp, const char *delim);
char	*ft_strrchr(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_str_malloc(int n, char c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_subfstr(char *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int i);
char	*ft_itoa_base(unsigned int i, char *base);
char	*ft_itoa_base_long(unsigned long nbr, char *base);
char	*ft_itoa_unsigned(unsigned int i);
int		get_next_line(int fd, char **line);
int		ft_pow(int nb, int power);
double	ft_round(double nb,int round);
#endif

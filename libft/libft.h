/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:58:48 by phunguye          #+#    #+#             */
/*   Updated: 2022/03/20 10:58:48 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

/*is------------------------------------------------------------------*/
//ft_isalnum: alphanumeric character test
int		ft_isalnum(int c);
//ft_isalpha: alphabet character test 
int		ft_isalpha(int c);
//ft_is ascii: is ascii character test
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
/*mem-----------------------------------------------------------------*/
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
/*put-----------------------------------------------------------------*/
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putchar(char c);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putnstr_fd(char *s, int len, int fd);
/*str-----------------------------------------------------------------*/
//ft_strchr: locate character in string
char	*ft_strchr(const char *str, int c);
//ft_strlcat: size-bounded string copying and concatenation
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
//ft_strlcpy: size-bounded string copying and concatenation
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
//ft_strlen: find length of string
size_t	ft_strlen(const char *s);
//ft_strncmp: compare strings
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//ft_strnstr: locate a substring in a string
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
//ft_strdup: save a copy of a string
char	*ft_strdup(const char *s1);
//ft_strtrim:
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strrchr(const char *s, int c);
//char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
/*to------------------------------------------------------------------*/
char	*ft_itoa(int n);
int		ft_atoi(char const *str);
int		ft_tolower(int c);
int		ft_toupper(int c);
size_t	ft_wordcount(char const *s, char c);

#endif
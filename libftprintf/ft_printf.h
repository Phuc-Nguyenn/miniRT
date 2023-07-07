/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:22:20 by phunguye          #+#    #+#             */
/*   Updated: 2022/12/02 15:43:59 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include "./libft/libft.h"

int		ft_printf(const char *format, ...);
int		ft_eval_format(va_list args, const char format);
int		ft_print_char(int c);

int		ft_print_percent(void);
int		ft_print_str(char *str);
int		ft_print_ptr(unsigned long ptr);
int		ft_print_nbr(int nbr);
int		ft_print_unbr(unsigned int unbr);

int		ft_ptrlen(uintptr_t n);
void	ft_putptr(uintptr_t n);
int		ft_nbrlen(int n);
int		ft_unbrlen(unsigned int n);
void	ft_putunbr_fd(unsigned int n, int fd);

int		ft_hexlen(unsigned int n);
void	ft_puthex(unsigned int n, const char format);
int		ft_print_hex(unsigned int nbr, const char format);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:20:16 by phunguye          #+#    #+#             */
/*   Updated: 2022/12/02 15:42:38 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_percent(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_eval_format(va_list args, const char format)
{
	int	print_count;

	print_count = 0;
	if (format == 'c')
		print_count += ft_print_char(va_arg(args, int));
	else if (format == 's')
		print_count += ft_print_str(va_arg(args, char *));
	else if (format == 'p')
		print_count += ft_print_ptr(va_arg(args, unsigned long));
	else if (format == 'd' || format == 'i')
		print_count += ft_print_nbr(va_arg(args, int));
	else if (format == 'u')
		print_count += ft_print_unbr(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_count += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		print_count += ft_print_percent();
	return (print_count);
}

int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		print_count;

	i = 0;
	print_count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
			print_count += ft_eval_format(args, str[i++ + 1]);
		else
			print_count += ft_print_char(str[i]);
		i++;
	}
	va_end(args);
	return (print_count);
}

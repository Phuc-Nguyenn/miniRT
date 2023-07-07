/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 12:17:50 by phunguye          #+#    #+#             */
/*   Updated: 2022/05/01 12:17:50 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexlen(unsigned int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		len++;
		n /= 16;
	}
	return (len);
}

void	ft_puthex(unsigned int n, const char format)
{
	const char	*digits = "0123456789abcdef";
	const char	*capdigits = "0123456789ABCDEF";

	if (n >= 16)
		ft_puthex(n / 16, format);
	if (format == 'X')
		ft_putchar_fd(capdigits[n % 16], 1);
	else
		ft_putchar_fd(digits[n % 16], 1);
}

int	ft_print_hex(unsigned int nbr, const char format)
{
	int	count;

	ft_puthex(nbr, format);
	count = ft_hexlen(nbr);
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 12:50:31 by phunguye          #+#    #+#             */
/*   Updated: 2022/05/01 12:50:31 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptrlen(uintptr_t n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n /= 16;
	}
	return (len);
}

void	ft_putptr(uintptr_t n)
{
	const char	*digits = "0123456789abcdef";

	if (n >= 16)
		ft_putptr(n / 16);
	ft_putchar_fd(digits[n % 16], 1);
}

int	ft_nbrlen(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		count += 1;
		if (n == -2147483648)
			n = 2147483647;
		else
			n *= -1;
	}
	while (!(n < 10))
	{
		n /= 10;
		count += 1;
	}
	return (count);
}

int	ft_unbrlen(unsigned int n)
{
	int	count;

	count = 0;
	if (!(n / 10))
		return (1);
	count = (1 + ft_unbrlen(n / 10));
	return (count);
}

void	ft_putunbr_fd(unsigned int n, int fd)
{
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + 48, fd);
}

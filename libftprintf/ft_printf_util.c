/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 12:18:30 by phunguye          #+#    #+#             */
/*   Updated: 2022/05/01 12:18:30 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *str)
{
	int	count;

	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	count = ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (count);
}

int	ft_print_ptr(unsigned long ptr)
{
	int	count;

	count = write(1, "0x", 2);
	if (ptr == 0)
		count += write(1, "0", 1);
	else
	{
		ft_putptr(ptr);
		count += ft_ptrlen(ptr);
	}
	return (count);
}

int	ft_print_nbr(int nbr)
{
	int	count;

	count = ft_nbrlen(nbr);
	ft_putnbr_fd(nbr, 1);
	return (count);
}

int	ft_print_unbr(unsigned int unbr)
{
	int	count;

	count = ft_unbrlen(unbr);
	ft_putunbr_fd(unbr, 1);
	return (count);
}

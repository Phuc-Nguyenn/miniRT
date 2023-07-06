/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:57:03 by phunguye          #+#    #+#             */
/*   Updated: 2022/03/20 10:57:52 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnstr_fd(char *s, int len, int fd)
{
	int		i;

	i = 0;
	while (s[i] && i < len)
		ft_putchar_fd(s[i++], fd);
}

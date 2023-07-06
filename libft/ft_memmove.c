/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:56:10 by phunguye          #+#    #+#             */
/*   Updated: 2022/03/20 10:56:13 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = -1;
	if (src < dst)
		while ((int)(--len) >= 0)
			*(char *)(dst + len) = *(char *)(src + len);
	else
		while (++i < len)
			*(char *)(dst + i) = *(char *)(src + i);
	return (dst);
}

//he memmove() function copies count bytes of src to dest {allows overlap}
//would this work with (int *) instead of (char *) does it matter what you use?
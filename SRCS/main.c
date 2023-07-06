/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:32:34 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/07 00:56:18 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int initialise_mlx(t_mlxdata *mlxdata) {
	mlxdata->mlx_ptr = mlx_init();
	mlxdata->wdw_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "miniRT");
	void	*img_ptr;
	char	*string;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}

int main(void)
{
	t_mlxdata mlxdata;
	
	if(!initialise_mlx(&mlxdata))
		ft_printf("minilibx structure initialisation failed");
	miniRT(mlxdata);
}
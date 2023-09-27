/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:32:34 by phunguye          #+#    #+#             */
/*   Updated: 2023/09/27 22:58:52 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void ft_miniRT(t_miniRT *miniRT) 
{
	//clear_screen(&(miniRT->mlxdata));
  viewport_init(&(miniRT->camera));
	rays_init(&(miniRT->camera), &(miniRT->rays));
	get_shapes(&(miniRT->shapes));
	get_lights(&(miniRT->lights));
	make_scene(miniRT->rays, miniRT->shapes, miniRT->lights);
  
	//shadows(miniRT->rays, miniRT->shapes, miniRT->lights); -> placed into make_scene
	//ambience(rays);
	viewport_to_image(&(miniRT->mlxdata), &(miniRT->rays));
	mlx_put_image_to_window(miniRT->mlxdata.mlx_ptr,miniRT->mlxdata.win_ptr, miniRT->mlxdata.img_ptr, 0, 0);
}

int main(void)
{
  t_miniRT miniRT;
	if(initialise_mlx(&(miniRT.mlxdata)) == -1)
		ft_printf("minilibx structure initialisation failed");
  camera_init(&(miniRT.camera));
	ft_miniRT(&miniRT);
  mlx_key_hook(miniRT.mlxdata.win_ptr, key_hook, &miniRT);
  mlx_hook(miniRT.mlxdata.win_ptr, 17, 0, (void *)exit, 0);
	mlx_loop(miniRT.mlxdata.mlx_ptr);
	return(0);
}

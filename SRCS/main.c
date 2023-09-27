/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:32:34 by phunguye          #+#    #+#             */
/*   Updated: 2023/09/26 16:19:57 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

/*calculates whether a particular ray should be in shadow and change
its colour to ambient accordingly*/
void shadows(t_ray *rays, t_shapes *shapes, t_light *lights) {
	float shdw_distance;
	for(int i = 0; i < W_WIDTH * W_HEIGHT; i++) {
		for(int s = 0; s < 3; s++)
			if(in_sph_shadow(&rays[i], &(shapes->circles[s]), lights, &shdw_distance))
			{
				rays[i].colour = colour_factor(rays[i].colour, 0.2);
				rays[i].colour = colour_desat(rays[i].colour, 0.5);
				rays[i].colour = shdw_adjust_lume(rays[i].colour);
			}
		//for(int p = 0; p < 1; p++)
			//in_pln_shadow()
	}
}

/*calculates the intersections between rays and its closest object*/
void intersections(t_ray *rays, t_shapes *shapes, t_light *lights)
{
	for(int i = 0; i < W_WIDTH * W_HEIGHT; i++) {
		for(int s = 0; s < 3; s++)//changes num of sph
			sph_intersects(&rays[i], &(shapes->circles[s]), lights);
		for(int p = 0; p < 4; p++) //num of planes
			pln_intersects(&rays[i], &(shapes->planes[p]), lights);
    
	}
}

void bounce(t_ray *rays, t_shapes *shapes)
{
  for(int i = 0; i < W_WIDTH * W_HEIGHT; i++)
  {
    rays[i].direction = rand_vct();
    
  }
}

void ft_miniRT(t_miniRT *miniRT) {

	//clear_screen(&(miniRT->mlxdata));
  viewport_init(&(miniRT->camera));
	rays_init(&(miniRT->camera), &(miniRT->rays));
	get_shapes(&(miniRT->shapes));
	get_lights(&(miniRT->lights));
	intersections(miniRT->rays, miniRT->shapes, miniRT->lights);
  
	shadows(miniRT->rays, miniRT->shapes, miniRT->lights);
  //bounce(miniRT->rays, miniRT-> shapes, miniRT-> lights);
  
	//ambience(rays);
	viewport_to_image(&(miniRT->mlxdata), &(miniRT->rays));
	mlx_put_image_to_window(miniRT->mlxdata.mlx_ptr,miniRT->mlxdata.win_ptr, miniRT->mlxdata.img_ptr, 0, 0);
}

int	key_hook(int keycode, t_miniRT *miniRT)
{
	if (keycode == 97){
		miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(-0.5,0,0,0));
    printf("moved left\n");
  }
	if (keycode == 100)
  {
		miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(0.5,0,0,0));
    printf("moved right\n");
  }
	ft_miniRT(miniRT);
	return (0);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:32:34 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/15 11:48:41 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int in_sph_shadow(t_ray *ray, t_cir *sphere, t_light *lights) {
	t_ray to_lgt;
	to_lgt.start_pos = vct_scalar_prod((*ray).parameter, (*ray).direction);
	to_lgt.direction = vct_sub(lights[0].pos, to_lgt.start_pos);

	float a = vct_dot_prod(to_lgt.direction,to_lgt.direction);
	float b = 2*(vct_dot_prod(to_lgt.start_pos,to_lgt.direction)
		- vct_dot_prod(to_lgt.direction,(*sphere).center));
	float c = -2 * vct_dot_prod((*sphere).center, to_lgt.start_pos)
		+ vct_dot_prod(to_lgt.start_pos,to_lgt.start_pos)
		+ vct_dot_prod((*sphere).center, (*sphere).center)
		- ((*sphere).radius * (*sphere).radius);
	if(discrim(a,b,c) >= 0) {
		float param = quadratic_sol(a,b,c);
		if(param > 0)
			return(1);
	}
	return(0);
}

/*calculates the intersections between ray and object*/
void intersections(t_ray *rays, t_shapes *shapes, t_light *lights)
{
	for(int i = 0; i < W_WIDTH * W_HEIGHT; i++) {
		for(int s = 0; s < 3; s++)//changes num of sph
			sph_intersects(&rays[i], &(shapes->circles[s]), lights);
		for(int p = 0; p < 1; p++)
			pln_intersects(&rays[i], &(shapes->planes[0]), lights);
		for(int s = 0; s < 3; s++)
			if(in_sph_shadow(&rays[i], &(shapes->circles[s]), lights))
				rays[i].colour = get_colour(1,1,1,AMBIENT);
		//for(int p = 0; p < 1; p++)
			//in_pln_shadow()
	}
}

void viewport_to_image(t_mlxdata *mlxdata, t_ray **rays) {
	int i = 0;
	for(int y = 0; y < W_HEIGHT; y++) {
		for(int x = 0; x < W_WIDTH; x++) {
			ft_pixelput(mlxdata, x, y, (*rays)[i].colour);
			i++;
		}
	}
}


void miniRT(t_mlxdata *mlxdata) {
	t_camera camera;
	t_ray *rays;
	t_shapes *shapes;
	t_light *lights;

	clear_screen(mlxdata);
	camera_init(&camera);
	viewport_init(&camera);
	rays_init(&camera, &rays);
	get_shapes(&shapes);
	get_lights(&lights);
	intersections(rays, shapes, lights);
	//shadows(rays, shapes, lights)

	viewport_to_image(mlxdata, &rays);
	
	mlx_put_image_to_window(mlxdata->mlx_ptr, mlxdata->win_ptr, mlxdata->img_ptr, 0, 0);
}

int main(void)
{
	t_mlxdata mlxdata;
	
	if(initialise_mlx(&mlxdata) == -1)
		ft_printf("minilibx structure initialisation failed");
	miniRT(&mlxdata);
	mlx_loop(mlxdata.mlx_ptr);
	return(0);
}
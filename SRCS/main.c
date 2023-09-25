/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:32:34 by phunguye          #+#    #+#             */
/*   Updated: 2023/09/25 23:42:35 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

/*returns 0 if the vct does not hit the sphere
returns 1 if the vct does hit the sphere*/
int intsct_current(t_ray to_lgt, t_cir *sphere) {
	t_vct hit_coord = vct_add(to_lgt.start_pos, to_lgt.direction);
	float dis = (hit_coord.x-sphere->center.x)*(hit_coord.x-sphere->center.x)
	+ (hit_coord.y-sphere->center.y)*(hit_coord.y-sphere->center.y)
	+ (hit_coord.z-sphere->center.z)*(hit_coord.z-sphere->center.z)
	- (sphere->radius)*(sphere->radius);
	if(dis < 0.0001)
		return (1);
	return(0);
}

int in_sph_shadow(t_ray *ray, t_cir *sphere, t_light *lights, float *shdw_distance) {
	t_ray to_lgt;
	to_lgt.start_pos = vct_add(ray->start_pos, vct_scalar_prod((*ray).parameter, (*ray).direction));
	to_lgt.direction = vct_sub(lights[0].pos, to_lgt.start_pos);
	to_lgt.mag = vct_magnitude(to_lgt.direction);

	float a = vct_dot_prod(to_lgt.direction,to_lgt.direction);
	float b = 2*(vct_dot_prod(to_lgt.start_pos,to_lgt.direction)
		- vct_dot_prod(to_lgt.direction,(*sphere).center));
	float c = -2 * vct_dot_prod((*sphere).center, to_lgt.start_pos)
		+ vct_dot_prod(to_lgt.start_pos,to_lgt.start_pos)
		+ vct_dot_prod((*sphere).center, (*sphere).center)
		- ((*sphere).radius * (*sphere).radius);
	if(discrim(a,b,c) >= 0) {
		float param = quadratic_sol(a,b,c);
		//float param2 = quadratic_sol2(a,b,c);
		*shdw_distance = vct_magnitude(vct_scalar_prod(param, to_lgt.direction));
		if(param > 0.0001 && to_lgt.mag > *shdw_distance)
			return(1);
	}
	return(0);
}


int colour_to_ambient(int colour, float ambient){
	int r = (colour >> 16) & 0xff;
    int g = (colour >> 8) & 0xff;
    int b = colour & 0xff;
	float lume = (r+b+g)/3;

	if(lume < ambient){
		float multiplier = ambient * 255 / lume;
		r = (int)(r * multiplier);
		g = (int)(g * multiplier);
		b = (int)(g * multiplier);
	}
	colour = ((r << 16) & 0xff0000) | ((g << 8) & 0x00ff00) | (b & 0x0000ff);
    return colour;
}

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
				
				// float dist_factor = fmax(0,fmin(1,5/(0.5*shdw_distance)));
				// rays[i].colour = colour_add(rays[i].colour, round(-50), 
				// 	round(-50), round(-50), 0);
				// rays[i].colour = colour_desat(rays[i].colour, 0.5);
				// rays[i].colour = shdw_adjust_lume(rays[i].colour);
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

void viewport_to_image(t_mlxdata *mlxdata, t_ray **rays) {
	int i = 0;
	for(int y = 0; y < W_HEIGHT; y++) {
		for(int x = 0; x < W_WIDTH; x++) {
			ft_pixelput(mlxdata, x, y, (*rays)[i].colour);
			i++;
		}
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
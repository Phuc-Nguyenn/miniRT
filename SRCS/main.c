/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:32:34 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/10 13:32:41 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int initialise_mlx(t_mlxdata *mlxdata) {
	mlxdata->mlx_ptr = mlx_init();
	mlxdata->win_ptr = mlx_new_window(mlxdata->mlx_ptr, W_WIDTH, W_HEIGHT, "miniRT");
	mlxdata->img_ptr = mlx_new_image(mlxdata->mlx_ptr, W_WIDTH, W_HEIGHT);
	mlxdata->img_string = mlx_get_data_addr(mlxdata->img_ptr, &(mlxdata->bits_per_pixel), &(mlxdata->line_length), &(mlxdata->endian));
	if(mlxdata->mlx_ptr == NULL || mlxdata->win_ptr == NULL || mlxdata->img_ptr == NULL || mlxdata->img_string == NULL || 
		mlxdata->bits_per_pixel == 0 || mlxdata->line_length == 0)
		return(-1);
	return(1);
}

void camera_init(t_camera *camera) {
	camera->view_point = set_vct(0, 0, 0, 0);
	camera->orientation = set_vct(0, 0, 1, 0);
	camera->fov = 53;
	camera->projection_distance = 5;
}

/*calculates the coordinates corresponding to the camera's coordinates*/
void viewport_init(t_camera *camera) {
	float pixel_dimension;
	int i = 0;
	camera->viewport = (t_vct *)malloc(sizeof(t_vct) * W_HEIGHT * W_WIDTH);
	for(int y = -(W_HEIGHT/2); y < W_HEIGHT/2; y++) {
		for(int x = -(W_WIDTH/2); x < W_WIDTH/2; x++) {
			pixel_dimension = 2*camera->projection_distance*tan((camera->fov/2)*((M_PI/180.0)))/W_WIDTH;
			camera->viewport[i].x = camera->view_point.x + x * pixel_dimension;
			camera->viewport[i].y = camera->view_point.y + y * pixel_dimension;
			camera->viewport[i].z = camera->view_point.z + camera->projection_distance;
			//printf("[x,y,z] = %f, %f, %f\n", camera->viewport[i].x, camera->viewport[i].y, camera->viewport[i].z);
			i++;
		}
	}
}

void rays_init(t_camera *camera, t_ray **rays)
{
	*rays = malloc(sizeof(t_ray) * W_WIDTH * W_HEIGHT);
	int i;
	for(i = 0; i < W_WIDTH * W_HEIGHT; i++) {
		(*rays)[i].start_pos = camera->view_point;
		(*rays)[i].direction = vct_sub(camera->viewport[i],camera->view_point);
		//printf("[x,y,z] = %f, %f, %f\n", rays[i].direction.x, rays[i].direction.y, rays[i].direction.z);
		(*rays)[i].colour = BLACK;
		(*rays)[i].parameter = 0;
	}
}

void get_shapes(t_shapes **shapes) {
	*shapes = malloc(sizeof(t_shapes) * 1);
	(*shapes)->circles = malloc(sizeof(t_cir) * 3);
	/*basic circle (to be changed)*/
	(*shapes)->circles[0].center = set_vct(2, 0, 15, 0);
	(*shapes)->circles[0].radius = 2;
	(*shapes)->circles[0].colour = RED;

	(*shapes)->circles[1].center = set_vct(1, 0, 40, 0);
	(*shapes)->circles[1].radius = 3;
	(*shapes)->circles[1].colour = GREEN;

	(*shapes)->circles[2].center = set_vct(-3, 0, 20, 0);
	(*shapes)->circles[2].radius = 1;
	(*shapes)->circles[2].colour = BLUE;
}

int get_colour(float r, float g, float b, float l) {
	int hex_val;
	int red;
	int grn;
	int blu;
	r *= l;
	g *= l;
	b *= l;

	red = (int)(r*255);
	grn = (int)(g*255);
	blu = (int)(b*255);
	hex_val = (red << 16) | (grn << 8) | blu;
	return(hex_val);
}

/*calculates the intersections between ray and object*/
void intersections(t_ray *rays, t_shapes *shapes)
{
	for(int i = 0; i < W_WIDTH * W_HEIGHT; i++) {
		for(int s = 0; s < 3; s++) //changes num of sph
			sph_intersects(&rays[i], &(shapes->circles[s]));
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

void get_lights(t_light **lights) {
	*lights = malloc(sizeof(t_light) * 1);
	(*lights)[0].pos = set_vct(3, 0, 15, 0);
	(*lights)[0].lume = 1;
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
	intersections(rays, shapes);

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
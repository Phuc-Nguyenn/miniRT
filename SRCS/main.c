/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:32:34 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/14 20:12:02 by phunguye         ###   ########.fr       */
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
			camera->viewport[i].y = camera->view_point.y - y * pixel_dimension;
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
	*shapes = malloc(sizeof(t_shapes) * 2);
	(*shapes)->circles = malloc(sizeof(t_cir) * 3);
	/*basic circle (to be changed)*/
	(*shapes)->circles[0].center = set_vct(-3, -2, 40, 0);
	(*shapes)->circles[0].radius = 2;
	(*shapes)->circles[0].colour = RED;

	(*shapes)->circles[1].center = set_vct(0, -2, 20, 0);
	(*shapes)->circles[1].radius = 2;
	(*shapes)->circles[1].colour = GREEN;

	(*shapes)->circles[2].center = set_vct(3, -2, 30, 0);
	(*shapes)->circles[2].radius = 2;
	(*shapes)->circles[2].colour = BLUE;

	(*shapes)->planes = malloc(sizeof(t_pln) * 1);
	//planes (to be changed*)
	(*shapes)->planes[0].point = set_vct(0,-5,0,0);
	(*shapes)->planes[0].norm = set_vct(0,1,0,0);
	(*shapes)->planes[0].colour = WHITE;
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

float calc_pln_colour(t_ray ray, t_pln plane, t_light *lights){
	t_vct intsct_pt = vct_scalar_prod(ray.parameter,ray.direction);
	t_vct norm = plane.norm;
	t_vct to_lgt = vct_sub(lights[0].pos, intsct_pt);
	float cos_theta = vct_dot_prod(norm , to_lgt)/(vct_magnitude(norm)*vct_magnitude(to_lgt));
	if(cos_theta < 0)
		cos_theta = cos_theta * -1;
	cos_theta = 1-acos(cos_theta)/(M_PI/2);
	float luminosity = 1;
	luminosity = cos_theta;
	return(luminosity);
}

void pln_intersects(t_ray *ray, t_pln *plane, t_light *lights) {
	float D = (*plane).norm.x * (*plane).point.x
			+ (*plane).norm.y * (*plane).point.y
			+ (*plane).norm.z * (*plane).point.z;
	float numer = (*plane).norm.x * (*ray).start_pos.x
					+ (*plane).norm.y * (*ray).start_pos.y
					+ (*plane).norm.z * (*ray).start_pos.z;
	float denom = (*plane).norm.x * (*ray).direction.x
				+ (*plane).norm.y * (*ray).direction.y
				+ (*plane).norm.z * (*ray).direction.z;
	float intsct_param = (D-numer)/denom;
	if (intsct_param >= 0) {
		t_vct intsct_pt = vct_scalar_prod(intsct_param,(*ray).direction);
		t_ray tmp;
		tmp.direction = ray->direction;
		tmp.start_pos = ray->start_pos;
		tmp.parameter = intsct_param;
		float luminosity = calc_pln_colour(tmp, (*plane), lights);
		float mag = vct_magnitude(vct_sub(tmp.start_pos, intsct_pt));
		if(mag < ray->mag || ray->mag == 0) {
			//ray->colour = sphere->colour;
			ray->mag = mag;
			ray->colour = get_colour(1,1,1,luminosity);
			ray->parameter = intsct_param;
		}
	}
}

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
				rays[i].colour = get_colour(1,1,1,BLACK);
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

void get_lights(t_light **lights) {
	*lights = malloc(sizeof(t_light) * 1);
	(*lights)[0].pos = set_vct(0, 5, 0, 0);
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
	intersections(rays, shapes, lights);

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:42:21 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/16 16:06:17 by phunguye         ###   ########.fr       */
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
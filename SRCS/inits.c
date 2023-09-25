/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:42:21 by phunguye          #+#    #+#             */
/*   Updated: 2023/09/25 23:36:28 by phunguye         ###   ########.fr       */
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
	camera->fov = 69;
	camera->projection_distance = 5;
}

/*calculates the coordinates corresponding to the camera's coordinates*/
void viewport_init(t_camera *camera) {
  int i = 0;
	float pixel_dimension;
	camera->viewport = (t_vct *)malloc(sizeof(t_vct) * W_HEIGHT * W_WIDTH);
  for(int y = (W_HEIGHT/2); y > -W_HEIGHT/2; y--) {
    for(int x = -(W_WIDTH/2); x < W_WIDTH/2; x++) {
      pixel_dimension = 2*camera->projection_distance*tan((camera->fov/2)*((M_PI/180.0)))/W_WIDTH;
      // camera->viewport[i].x = camera->view_point.x + x * pixel_dimension;
      // camera->viewport[i].y = camera->view_point.y + y * pixel_dimension;
      // camera->viewport[i].z = camera->view_point.z + camera->projection_distance;
      t_vct x_dir = vct_cross_prod(set_vct(0,1,0,0),camera->orientation);
      t_vct y_dir = vct_cross_prod(x_dir, vct_scalar_prod(-1,camera->orientation));
      t_vct x_vct = vct_scalar_prod(x * pixel_dimension,unit_vct(x_dir));
      t_vct y_vct = vct_scalar_prod(y * pixel_dimension,unit_vct(y_dir));
      camera->viewport[i] = vct_add(camera->view_point, vct_scalar_prod(camera->projection_distance, unit_vct(camera->orientation)));
      camera->viewport[i] = vct_add(camera->viewport[i], x_vct);
      camera->viewport[i] = vct_add(camera->viewport[i], y_vct);
      //printf("[x,y,z] = %f, %f, %f\n", x_dir.x, x_dir.y, x_dir.z);
      i++;
    }
  }
}

void rays_init(t_camera *camera, t_ray **rays)
{
	*rays = malloc(sizeof(t_ray) * W_WIDTH * W_HEIGHT);
	for(int i = 0; i < W_WIDTH * W_HEIGHT; i++) {
		(*rays)[i].start_pos = camera->view_point;
		(*rays)[i].direction = unit_vct(vct_sub(camera->viewport[i],camera->view_point));
		//printf("[x,y,z] = %f, %f, %f\n", (*rays)[i].start_pos.x, (*rays)[i].start_pos.y, (*rays)[i].start_pos.z);
		(*rays)[i].colour = BLACK;
		(*rays)[i].parameter = 0;
	}
}
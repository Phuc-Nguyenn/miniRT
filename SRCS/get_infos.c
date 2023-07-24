/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tytang <tytang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:44:11 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/24 13:26:10 by tytang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void get_lights(t_light **lights, t_mlxdata *mlxdata) {
	*lights = malloc(sizeof(t_light) * 1);
	//(*lights)[0].pos = set_vct(3, 20, 12, 0);
	
    //using user input
    int l_x = mlxdata->initial_struct->light_xyz[0];
	int l_y = mlxdata->initial_struct->light_xyz[1];
	int l_z = mlxdata->initial_struct->light_xyz[2];

	(*lights)[0].pos = set_vct(l_x, l_y, l_z, 0);
    (*lights)[0].lume = 1;
}

void get_shapes(t_shapes **shapes, t_mlxdata *mlxdata) {
    printf("inside get_shapes\n");
    printf("(get_shapes) mlxdata->initial_struct->sphere_init[%d].sphere_xyz[0]: %f\n", 0, mlxdata->initial_struct->sphere_init[0].sphere_xyz[0]);

	*shapes = malloc(sizeof(t_shapes) * 2);

    int num_of_spheres = mlxdata->initial_struct->sphere_count;
	int num_of_planes = mlxdata->initial_struct->plane_count;
	int num_of_cylinder = mlxdata->initial_struct->cylinder_count;

    //basic circle (to be changed)
    //printf("not allocated cirle memory\n");

	(*shapes)->circles = malloc(sizeof(t_cir) * num_of_spheres);
    printf("allocated cirle memory\n");
    int ctr = 0;
    printf("num_of_spheres: %d\n", num_of_spheres);
    printf("(get_shapes) mlxdata->initial_struct->sphere_init[%d].sphere_xyz[0]: %f\n", 0, mlxdata->initial_struct->sphere_init[0].sphere_xyz[0]);

	while (ctr < num_of_spheres-1)
	{
        printf("(get_shapes) mlxdata->initial_struct->sphere_init[%d].sphere_xyz[0]: %f\n", ctr, mlxdata->initial_struct->sphere_init[ctr].sphere_xyz[0]);
		(*shapes)->circles[ctr].center = set_vct(
			mlxdata->initial_struct->sphere_init[ctr].sphere_xyz[0],
			mlxdata->initial_struct->sphere_init[ctr].sphere_xyz[1],
			mlxdata->initial_struct->sphere_init[ctr].sphere_xyz[2], 0);
        printf("(get_shapes) mlxdata->initial_struct->sphere_init[%d].sphere_xyz[0]: %f\n", ctr, mlxdata->initial_struct->sphere_init[ctr].sphere_xyz[0]);
		(*shapes)->circles[ctr].radius = mlxdata->initial_struct->sphere_init[ctr].sphere_diameter / 2;
		(*shapes)->circles[ctr].colour = RED;
		ctr++;
	}
    printf("finished number of circles\n");
	/*(*shapes)->circles[0].center = set_vct(3, 2, 20, 0);
	(*shapes)->circles[0].radius = 2;
	(*shapes)->circles[0].colour = 0x64b6ac;

	(*shapes)->circles[1].center = set_vct(-4, 0, 26, 0);
	(*shapes)->circles[1].radius = 2;
	(*shapes)->circles[1].colour = 0xffcdb2;

	(*shapes)->circles[2].center = set_vct(1, 15, 14, 0);
	(*shapes)->circles[2].radius = 2;
	(*shapes)->circles[2].colour = 0x6c5b7b;*/



	
	//planes (to be changed)
    (*shapes)->planes = malloc(sizeof(t_pln) * num_of_planes);
    ctr = 0;
	while (ctr < num_of_planes-1)
	{
		(*shapes)->planes[ctr].point = set_vct(
			mlxdata->initial_struct->plane_init[ctr].plane_xyz[0],
			mlxdata->initial_struct->plane_init[ctr].plane_xyz[1],
			mlxdata->initial_struct->plane_init[ctr].plane_xyz[2], 0);
		(*shapes)->planes[ctr].norm = set_vct(
			mlxdata->initial_struct->plane_init[ctr].plane_norm_vect[0],
			mlxdata->initial_struct->plane_init[ctr].plane_norm_vect[1],
			mlxdata->initial_struct->plane_init[ctr].plane_norm_vect[2], 0);
		(*shapes)->planes[ctr].colour = 0xb70a61;
		ctr++;
	}
    printf("finished number of planes\n");
	/*(*shapes)->planes[0].point = set_vct(0,0,35,0);
	(*shapes)->planes[0].norm = set_vct(0,0,1,0);
	(*shapes)->planes[0].colour = 0xd77a61;

	(*shapes)->planes[1].point = set_vct(0,-2,0,0);
	(*shapes)->planes[1].norm = set_vct(0,1,0,0);
	(*shapes)->planes[1].colour = 0xa39fe1;
	
	(*shapes)->planes[2].point = set_vct(-7,0,0,0);
	(*shapes)->planes[2].norm = set_vct(1,0,0,0);
	(*shapes)->planes[2].colour = 0xdeb3e0;

	(*shapes)->planes[3].point = set_vct(7,0,0,0);
	(*shapes)->planes[3].norm = set_vct(1,0,0,0);
	(*shapes)->planes[3].colour = 0xffdde4;*/
}
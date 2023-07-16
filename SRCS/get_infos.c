/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:44:11 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/16 17:05:10 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void get_lights(t_light **lights) {
	*lights = malloc(sizeof(t_light) * 1);
	(*lights)[0].pos = set_vct(0, 10, 15, 0);
	(*lights)[0].lume = 1;
}

void get_shapes(t_shapes **shapes) {
	*shapes = malloc(sizeof(t_shapes) * 2);
	(*shapes)->circles = malloc(sizeof(t_cir) * 3);
	/*basic circle (to be changed)*/
	(*shapes)->circles[0].center = set_vct(3, 2, 20, 0);
	(*shapes)->circles[0].radius = 2;
	(*shapes)->circles[0].colour = 0x64b6ac;

	(*shapes)->circles[1].center = set_vct(-4, 0, 28, 0);
	(*shapes)->circles[1].radius = 2;
	(*shapes)->circles[1].colour = 0xffcdb2;

	(*shapes)->circles[2].center = set_vct(-1, 4, 23, 0);
	(*shapes)->circles[2].radius = 2;
	(*shapes)->circles[2].colour = 0x6c5b7b;

	(*shapes)->planes = malloc(sizeof(t_pln) * 3);
	//planes (to be changed*)
	(*shapes)->planes[0].point = set_vct(0,-2,0,0);
	(*shapes)->planes[0].norm = set_vct(0,1,0,0);
	(*shapes)->planes[0].colour = 0xd77a61;
	
	(*shapes)->planes[1].point = set_vct(-7,0,0,0);
	(*shapes)->planes[1].norm = set_vct(1,0,0,0);
	(*shapes)->planes[1].colour = 0xd77a61;

	(*shapes)->planes[2].point = set_vct(7,0,0,0);
	(*shapes)->planes[2].norm = set_vct(1,0,0,0);
	(*shapes)->planes[2].colour = 0xd77a61;
}
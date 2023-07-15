/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:44:11 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/15 17:47:40 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void get_lights(t_light **lights) {
	*lights = malloc(sizeof(t_light) * 1);
	(*lights)[0].pos = set_vct(-4, 4, 18, 0);
	(*lights)[0].lume = 1;
}

void get_shapes(t_shapes **shapes) {
	*shapes = malloc(sizeof(t_shapes) * 2);
	(*shapes)->circles = malloc(sizeof(t_cir) * 3);
	/*basic circle (to be changed)*/
	(*shapes)->circles[0].center = set_vct(-2, -2, 40, 0);
	(*shapes)->circles[0].radius = 2;
	(*shapes)->circles[0].colour = RED;

	(*shapes)->circles[1].center = set_vct(-4, 1, 18, 0);
	(*shapes)->circles[1].radius = 2;
	(*shapes)->circles[1].colour = GREEN;

	(*shapes)->circles[2].center = set_vct(4, 7, 15, 0);
	(*shapes)->circles[2].radius = 0.5;
	(*shapes)->circles[2].colour = BLUE;

	(*shapes)->planes = malloc(sizeof(t_pln) * 1);
	//planes (to be changed*)
	(*shapes)->planes[0].point = set_vct(0,8,0,0);
	(*shapes)->planes[0].norm = set_vct(0,1,0,0);
	(*shapes)->planes[0].colour = WHITE;
}
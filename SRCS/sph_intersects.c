/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sph_intersects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:50:46 by phunguye          #+#    #+#             */
/*   Updated: 2023/09/25 09:05:35 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniRT.h"

/*returns a normal unit vector to a sphere*/
t_vct sphere_normal(t_cir sphere, t_vct intersection_point){
	t_vct normal;

	normal = vct_sub(intersection_point, sphere.center);
	normal = unit_vct(normal);
	return(normal);
}

float calc_sph_colour(t_ray ray, t_cir sphere, t_light *lights){
	t_vct intsct_pt = vct_add(ray.start_pos, vct_scalar_prod(ray.parameter,ray.direction));
	t_vct norm = sphere_normal(sphere, intsct_pt);
	t_vct to_lgt = vct_sub(lights[0].pos, intsct_pt);
	float cos_theta = vct_dot_prod(norm, to_lgt)/(vct_magnitude(norm)*vct_magnitude(to_lgt));
	cos_theta = fmax(cos_theta, 0);
	cos_theta = 1-acos(cos_theta)/(M_PI/2);
	float luminosity = cos_theta;
	return(luminosity);
}

/*this function calculates whether a ray intersects a sphere
the ray keeps track of the closest intersection and the intersection
that gives it the lowest magnitude (closest intersection) gives it 
the colour*/
void sph_intersects(t_ray *ray, t_cir *sphere, t_light *lights){
	float a = vct_dot_prod((*ray).direction,(*ray).direction);
	float b = 2*(vct_dot_prod((*ray).start_pos,(*ray).direction)
		- vct_dot_prod((*ray).direction,(*sphere).center));
	float c = -2 * vct_dot_prod((*sphere).center, (*ray).start_pos)
		+ vct_dot_prod((*ray).start_pos,(*ray).start_pos)
		+ vct_dot_prod((*sphere).center, (*sphere).center)
		- ((*sphere).radius * (*sphere).radius);
	if(discrim(a,b,c) >= 0) {
		float intsct_param = quadratic_sol(a,b,c);
		if(intsct_param >= 0) {
			t_vct intsct_pt = vct_add((*ray).start_pos, vct_scalar_prod(intsct_param,(*ray).direction));
			t_ray tmp;
			tmp.direction = ray->direction;
			tmp.start_pos = ray->start_pos;
			tmp.parameter = intsct_param;
			float luminosity = calc_sph_colour(tmp, (*sphere), lights);
			float mag = vct_magnitude(vct_sub(tmp.start_pos, intsct_pt));
			if(mag < ray->mag || ray->mag == 0) {
				//ray->colour = sphere->colour;
				ray->mag = mag;
				luminosity = fmax(luminosity, AMBIENT);
				ray->colour = colour_factor(sphere->colour,luminosity);
				ray->parameter = intsct_param;
				}
		}
	}
}
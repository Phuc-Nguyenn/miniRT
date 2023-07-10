/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sph_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:50:46 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/10 17:15:26 by phunguye         ###   ########.fr       */
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

float calc_colour(t_ray ray, t_cir sphere){
	t_vct intsct_pt = vct_scalar_prod(ray.parameter,ray.direction);
	t_vct norm = sphere_normal(sphere, intsct_pt);
	t_vct b = vct_sub(set_vct(-8,4,10,0), intsct_pt);
	float cos_theta = vct_dot_prod(norm, b)/(vct_magnitude(norm)*vct_magnitude(b));
	cos_theta = fmax(cos_theta, 0);
	cos_theta = 1-acos(cos_theta)/(M_PI/2);
	float luminosity = 1;
	luminosity = cos_theta;
	return(luminosity);
}

void sph_intersects(t_ray *ray, t_cir *sphere){
	float a = vct_dot_prod((*ray).direction,(*ray).direction);
	float b = 2*(vct_dot_prod((*ray).start_pos,(*ray).direction)
		- vct_dot_prod((*ray).direction,(*sphere).center));
	float c = -2 * vct_dot_prod((*sphere).center, (*ray).start_pos)
		+ vct_dot_prod((*ray).start_pos,(*ray).start_pos)
		+ vct_dot_prod((*sphere).center, (*sphere).center)
		- ((*sphere).radius * (*sphere).radius);
	if(discrim(a,b,c) >= 0) {
		(*ray).parameter = quadratic_sol(a,b,c);
		if((*ray).parameter >= 0) {
			t_vct intsct_pt = vct_scalar_prod((*ray).parameter,(*ray).direction);
			float luminosity = calc_colour(*ray, *sphere);
			t_vct tmp = vct_sub((*ray).start_pos, intsct_pt);
			float mag = vct_magnitude(tmp);
			if(mag < ray->mag || ray->mag == 0) {
				ray->colour = get_colour(1,1,1,luminosity);
				//ray->colour = sphere->colour;
				ray->mag = mag;
			}
		}
	}
}
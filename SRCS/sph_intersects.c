/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sph_intersects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:50:46 by phunguye          #+#    #+#             */
/*   Updated: 2023/09/26 14:42:52 by phunguye         ###   ########.fr       */
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
      
			if(mag < ray->mag || ray->mag == 0) 
      {
				ray->mag = mag;
				luminosity = fmax(luminosity, AMBIENT);
				ray->colour = colour_factor(sphere->colour,luminosity);
				ray->parameter = intsct_param;
        ray->end_pos = intsct_pt;
			}
		}
	}
}

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
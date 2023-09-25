// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pln_intersects.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/15 11:37:16 by phunguye          #+#    #+#             */
// /*   Updated: 2023/09/25 09:22:37 by phunguye         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

# include "../miniRT.h"

float calculateCosineTheta(t_vct normal, t_vct to_light) {
    float dot_product = vct_dot_prod(normal, to_light);
    float norm_product = vct_magnitude(normal) * vct_magnitude(to_light);
    float cos_theta = fmaxf(0, dot_product / norm_product);
    return 1 - acosf(cos_theta) / (M_PI / 2);
}

void pln_intersects(t_ray *ray, t_pln *plane, t_light *lights) {
    float D = vct_dot_prod((*plane).norm, (*plane).point);
    float numer = vct_dot_prod((*plane).norm, (*ray).start_pos);
    float denom = vct_dot_prod((*plane).norm, (*ray).direction);

    if (denom == 0) return;  // Avoid division by zero

    float intsct_param = (D - numer) / denom;

    if (intsct_param >= 0) {
        t_vct intsct_pt = vct_add(ray->start_pos, vct_scalar_prod(intsct_param, ray->direction));
        float mag = vct_magnitude(vct_sub(ray->start_pos, intsct_pt));
        float distance_weight = 1 / (0.05f * mag + 1);
        float angle_weight = calculateCosineTheta(ray->direction, vct_sub(lights[0].pos, intsct_pt));
        float luminosity = distance_weight * 0.95 + angle_weight * 0.05;

        if (mag < ray->mag || ray->mag == 0) {
            ray->mag = mag;
            luminosity = fmaxf(luminosity, AMBIENT);
            ray->colour = colour_factor(plane->colour, luminosity);
            ray->parameter = intsct_param;
        }
    }
}

// # include "../miniRT.h"

// float calc_pln_colour(t_ray ray, t_pln plane, t_light *lights) {
// 	t_vct intsct_pt = vct_add(ray.start_pos, vct_scalar_prod(ray.parameter,ray.direction));
// 	t_vct norm = plane.norm;
// 	t_vct to_lgt = vct_sub(lights[0].pos, intsct_pt);
// 	float cos_theta = vct_dot_prod(norm , to_lgt)/(vct_magnitude(norm)*vct_magnitude(to_lgt));
// 	if(cos_theta < 0)
// 		cos_theta = cos_theta * -1;
// 	cos_theta = 1-acos(cos_theta)/(M_PI/2);
// 	float luminosity = 1;
// 	luminosity = cos_theta;
// 	return(luminosity);
// }

// void pln_intersects(t_ray *ray, t_pln *plane, t_light *lights) {
// 	float D = (*plane).norm.x * (*plane).point.x
// 			+ (*plane).norm.y * (*plane).point.y
// 			+ (*plane).norm.z * (*plane).point.z;
// 	float numer = (*plane).norm.x * (*ray).start_pos.x
// 					+ (*plane).norm.y * (*ray).start_pos.y
// 					+ (*plane).norm.z * (*ray).start_pos.z;
// 	float denom = (*plane).norm.x * (*ray).direction.x
// 				+ (*plane).norm.y * (*ray).direction.y
// 				+ (*plane).norm.z * (*ray).direction.z;
// 	float intsct_param = (D-numer)/denom;
// 	if (intsct_param >= 0) {
// 		t_vct intsct_pt = vct_add(ray->start_pos, vct_scalar_prod(intsct_param,(*ray).direction));
// 		t_ray tmp;
// 		tmp.direction = ray->direction;
// 		tmp.start_pos = ray->start_pos;
// 		tmp.parameter = intsct_param;
// 		float mag = vct_magnitude(vct_sub(tmp.start_pos, intsct_pt));
// 		float distance_weight = 1/(0.05*mag+1);
// 		float angle_weight = calc_pln_colour(tmp, (*plane), lights);
// 		float luminosity = distance_weight*0.95 + angle_weight*0.05;
// 		if(mag < ray->mag || ray->mag == 0) {
// 			//ray->colour = sphere->colour;
// 			ray->mag = mag;
// 			luminosity = fmax(luminosity, AMBIENT);
// 			ray->colour = colour_factor(plane->colour,luminosity);
// 			ray->parameter = intsct_param;
// 		}
// 	}
// }
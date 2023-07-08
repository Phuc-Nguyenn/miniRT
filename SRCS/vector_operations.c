/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:05:55 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/08 12:19:46 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniRT.h"

t_vector set_vct(float x, float y, float z, float alpha) {
	t_vector new;
	new.x = x;
	new.y = y;
	new.z = z;
	new.alpha = alpha;
	return(new);
}

t_vector vct_add(t_vector vct1, t_vector vct2) {
	t_vector new;
	new.x = vct1.x + vct2.x;
	new.y = vct1.y + vct2.y;
	new.z = vct1.z + vct2.z;
	return(new);
}

t_vector vct_sub(t_vector vct1, t_vector vct2) {
	t_vector new;
	new.x = vct1.x - vct2.x;
	new.y = vct1.y - vct2.y;
	new.z = vct1.z - vct2.z;
	return(new);
}

t_vector vct_scalar_prod(float scalar, t_vector vct1) {
	t_vector new;
	new.x = vct1.x * scalar;
	new.y = vct1.y * scalar;
	new.z = vct1.z * scalar;
	return(new);
}

float vct_magnitude(t_vector vct) {
	float magnitude;

	magnitude = sqrt(vct.x^2+vct.y^2+vct.z^2);
	return(magnitude);
}

t_vector unit_vct(t_vector direction) {
	t_vector unit_vct;
	float magnitude;

	magnitude = vct_magnitude(direction);
	unit_vct = direction * vct_scalar_prod(1/magnitude, direction);
	return(unit_vct);
}

t_vector vct_cross_prod(t_vector vct1, t_vector vct2) {
	t_vector new;
	new.x = vct1.y * vct2.z - vct1.z * vct2.y;
	new.y = vct1.x * vct2.z - vct1.z * vct2.x;
	new.z = vct1.x * vct2.y - vct1.y * vct2.x;
	return(new);
}
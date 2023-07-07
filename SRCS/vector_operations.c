/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:05:55 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/07 16:19:56 by phunguye         ###   ########.fr       */
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

t_vector vct_subtract(t_vector vct1, t_vector vct2) {
	t_vector new;
	new.x = vct1.x - vct2.x;
	new.y = vct1.y - vct2.y;
	new.z = vct1.z - vct2.z;
	return(new);
}

t_vector vct_scalar_prod(t_vector vct1, int scalar) {
	t_vector new;
	new.x = vct1.x * scalar;
	new.y = vct1.y * scalar;
	new.z = vct1.z * scalar;
	return(new);
}

t_vector vct_cross_prod(t_vector vct1, t_vector vct2) {
	t_vector new;
	new.x = vct1.y * vct2.z - vct1.z * vct2.y;
	new.y = vct1.x * vct2.z - vct1.z * vct2.x;
	new.z = vct1.x * vct2.y - vct1.y * vct2.x;
	return(new);
}
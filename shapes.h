/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:41:32 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/08 16:24:47 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H
# include "./miniRT.h"

typedef struct s_cir
{
	t_vct center;
	float radius;
} t_cir;

typedef struct s_shapes
{
	//t_pln *planes;
	t_cir *circles;
	//t_cyl *cylinders;
} t_shapes;


# endif


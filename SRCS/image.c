/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:34:53 by phunguye          #+#    #+#             */
/*   Updated: 2023/09/27 22:52:43 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniRT.h"

/*calculates whether a particular ray should be in shadow and change
its colour to ambient accordingly*/


/*calculates the intersections between rays and its closest object*/
void make_scene(t_ray *rays, t_shapes *shapes, t_light *lights)
{
	for(int i = 0; i < W_WIDTH * W_HEIGHT; i++) {
		for(int s = 0; s < 3; s++)//changes num of sph
			sph_intersects(&rays[i], &(shapes->circles[s]), lights);
		for(int p = 0; p < 4; p++) //num of planes
			pln_intersects(&rays[i], &(shapes->planes[p]), lights);
    float shdw_distance;
    for(int s = 0; s < 3; s++) {
			if(in_sph_shadow(&rays[i], &(shapes->circles[s]), lights, &shdw_distance))
			{
				rays[i].colour = colour_factor(rays[i].colour, 0.2);
				rays[i].colour = colour_desat(rays[i].colour, 0.5);
				rays[i].colour = shdw_adjust_lume(rays[i].colour);
			}
    }
	}
}

void viewport_to_image(t_mlxdata *mlxdata, t_ray **rays) {
	int i = 0;
	for(int y = 0; y < W_HEIGHT; y++) {
		for(int x = 0; x < W_WIDTH; x++) {
			ft_pixelput(mlxdata, x, y, (*rays)[i].colour);
			i++;
		}
	}
}

void	clear_screen(t_mlxdata *mlxdata)
{
	int	x;
	int	y;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
			ft_pixelput(mlxdata, x++, y, BLACK);
		y++;
	}
}
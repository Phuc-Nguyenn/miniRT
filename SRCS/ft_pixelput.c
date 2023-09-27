/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixelput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:18:48 by phunguye          #+#    #+#             */
/*   Updated: 2023/09/27 21:42:58 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniRT.h"

//changes the colour of a pixel in the pixel string to the colour
//the pixel is a 32 bit pixel
// xxxxxxxx xxxxxxx xxxxxxxx xxxxxxxx -> 32 bit integer
//   alpha    red     green    blue
//each one is an 8bit integer which ranges from 0 to 255
void	change_pixel_colour(char	*pixel_addr, int colour)
{
	pixel_addr[0] = (colour);
	pixel_addr[1] = (colour >> 8);
	pixel_addr[2] = (colour >> 16);
	pixel_addr[3] = (colour >> 24);
}

//translates space so origin is in the centre of screen
//and y goes upwards
void ft_translatedput(t_mlxdata *mlxdata, int x, int y, int colour) {
	x = x + 960;
	y = (-1 * y) + 520;
	ft_pixelput(mlxdata, x, y, colour);
}

//changes the colour of a pixel at x and y position
//	*it does this through calculating the index of the image string it must change
void	ft_pixelput(t_mlxdata *mlxdata, int x, int y, int colour)
{
	int	pixel;

	pixel = (mlxdata->line_length * y) + (x * 4);
	if (pixel >= 0 && pixel <= W_WIDTH * W_HEIGHT * 4)
		change_pixel_colour(&(mlxdata->img_string[pixel]), colour);
	else
		ft_printf("pixel of range");
	
}
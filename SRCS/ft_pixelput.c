/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixelput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:18:48 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/16 16:00:05 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int colour_desat(int colour, float desat_amt) {
    // Extract the individual RGB components from the color
    int r = (colour >> 16) & 0xff;
    int g = (colour >> 8) & 0xff;
    int b = colour & 0xff;

    // Calculate the average of the RGB components
    int avg = (r + g + b) / 3;

    // Calculate the new desaturated RGB values
    int desat_r = r + (int)((avg - r) * desat_amt);
    int desat_g = g + (int)((avg - g) * desat_amt);
    int desat_b = b + (int)((avg - b) * desat_amt);

    // Combine the desaturated RGB values back into a single color
    int desaturated_colour = (desat_r << 16) | (desat_g << 8) | desat_b;

    return desaturated_colour;
}

int colour_add(int colour, int r, int g, int b, int a) {
    r = fmin(255, fmax(0,(colour >> 16 & 0xff) + r));
    g = fmin(255, fmax(0,(colour >> 8 & 0xff) + g));
    b = fmin(255, fmax(0,(colour & 0xff) + b));

    colour = ((r << 16) & 0xff0000) | ((g << 8) & 0x00ff00) | (b & 0x0000ff);
    return colour;
}

int colour_factor(int colour, float factor) {
	int r = fmin(255, fmax(0,(colour >> 16 & 0xff)*factor));
    int g = fmin(255, fmax(0,(colour >> 8 & 0xff)*factor));
    int b = fmin(255, fmax(0,(colour & 0xff)*factor));

    colour = ((r << 16) & 0xff0000) | ((g << 8) & 0x00ff00) | (b & 0x0000ff);
    return colour;
}

/*converts decimal representation of r g b and l to a hex colour*/
int get_colour_dec(float r, float g, float b, float l) {
	int hex_val;
	int red;
	int grn;
	int blu;
	r *= l;
	g *= l;
	b *= l;

	red = (int)(r*255);
	grn = (int)(g*255);
	blu = (int)(b*255);
	hex_val = (red << 16) | (grn << 8) | blu;
	return(hex_val);
}

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
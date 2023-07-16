/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:18:28 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/16 18:01:29 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int shdw_adjust_lume(int colour) {
	int r = (colour >> 16) & 0xff;
    int g = (colour >> 8) & 0xff;
    int b = colour & 0xff;

	float ave_lume = (r+g+b)/3;
	float factor = fmin(1,fmax(0,atan(-0.003*(ave_lume-256))));
	//printf("%f	", factor);
	colour = colour_factor(colour, factor);
	return(colour);
}

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

/*outputs hexadecimal value from r g b from 0 to 255*/
int get_hex(int r, int g, int b) {
	int colour;

	colour = (r << 16) | (g << 8) | b;
	return(colour); 
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
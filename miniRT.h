/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:25:24 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/14 17:25:24 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "./libftprintf/ft_printf.h"
# include "./minilibx/mlx.h"
# include "./get_next_line/get_next_line.h"

# define W_WIDTH 1920
# define W_HEIGHT 1080

typedef struct s_vct
{
	float x;
	float y;
	float z;
	int alpha;
} t_vct;

typedef struct s_ray
{
	t_vct start_pos;
	t_vct direction;

	float mag;
	float parameter;
	float colour;
	float norm;
} t_ray;

//lume is the light's luminosity 0<=lume<=1
typedef struct s_light {
	t_vct pos;
	float lume;
} t_light;

/* camera is a structure containing everything relevant to the camera
 * view_point = the position of the camera
 * orientation = the direction the camera faces
 * viewport = the coordinates of the camera's pixels
 * fov = field of view of the camera -> used to calculate the viewport
 * projection_distance= how far the view port is from the position
 * what we actually see is the viewport.*/
typedef struct camera
{
	t_vct view_point;
	t_vct orientation;
	t_vct *viewport;
	float fov;
	float projection_distance;

} t_camera;

typedef struct s_mlxdata
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_string;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlxdata;

//shapes
typedef struct s_cir
{
	t_vct center;
	float radius;
	int colour;
} t_cir;

typedef struct s_pln{
	t_vct point;
	t_vct norm;
	int colour;
} t_pln;

typedef struct s_shapes
{
	t_pln *planes;
	t_cir *circles;
	//t_cyl *cylinders;
} t_shapes;

//sph_hit.c
void sph_intersects(t_ray *ray, t_cir *sphere, t_light *lights);
t_vct sphere_normal(t_cir sphere, t_vct intersection_point);


//ft_pixelput.c
void	ft_pixelput(t_mlxdata *mlxdata, int x, int y, int colour);
void	ft_translatedput(t_mlxdata *mlxdata, int x, int y, int colour);

//main.c
int initialise_mlx(t_mlxdata *mlxdata);

//image.c
void	clear_screen(t_mlxdata *mlxdata);

//vct_operations.c
t_vct set_vct(float x, float y, float z, float alpha);
t_vct vct_add(t_vct vct1, t_vct vct2);
t_vct vct_sub(t_vct vct1, t_vct vct2);
t_vct vct_scalar_prod(float scalar, t_vct vct1);
t_vct vct_cross_prod(t_vct vct1, t_vct vct2);
t_vct unit_vct(t_vct direction);
float vct_magnitude(t_vct vct);
float vct_dot_prod(t_vct vct1, t_vct vct2);
float discrim(float a, float b, float c);
float quadratic_sol(float a, float b, float c);



//colours
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

int get_colour(float r, float g, float b, float l);

#endif
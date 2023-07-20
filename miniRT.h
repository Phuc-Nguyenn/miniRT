/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tytang <tytang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:25:24 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/20 15:07:14 by tytang           ###   ########.fr       */
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
# include "./initalisation.h"
# include "./keys.h"

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
	t_inital_var *initial_struct;
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

//get_infos.c
void get_lights(t_light **lights, t_mlxdata *mlxdata);
void get_shapes(t_shapes **shapes, t_mlxdata *mlxdata);


//inits.c
void rays_init(t_camera *camera, t_ray **rays);
void viewport_init(t_camera *camera);
void camera_init(t_camera *camera, t_mlxdata *mlxdata);
int initialise_mlx(t_mlxdata *mlxdata);


//sph_intersects.c
void sph_intersects(t_ray *ray, t_cir *sphere, t_light *lights);
t_vct sphere_normal(t_cir sphere, t_vct intersection_point);

//pln_intersects.c
float calc_pln_colour(t_ray ray, t_pln plane, t_light *lights);
void pln_intersects(t_ray *ray, t_pln *plane, t_light *lights);
int colour_add(int colour, int r, int g, int b, int a);
int colour_factor(int colour, float factor);
int get_colour_dec(float r, float g, float b, float l);

//ft_pixelput.c
void	ft_pixelput(t_mlxdata *mlxdata, int x, int y, int colour);
void	ft_translatedput(t_mlxdata *mlxdata, int x, int y, int colour);

//colour.c
int get_colour_dec(float r, float g, float b, float l);
int colour_factor(int colour, float factor);
int colour_add(int colour, int r, int g, int b, int a);
int colour_desat(int colour, float desat_amt);
int shdw_adjust_lume(int colour);

//main.c
int initialise_mlx(t_mlxdata *mlxdata);
void shadows(t_ray *rays, t_shapes *shapes, t_light *lights);
void miniRT(t_mlxdata *mlxdata);

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
float quadratic_sol2(float a, float b, float c);

// in get_scene.c
int count_new_lines(char *src);
void initalise_lighting(char **current_string, t_mlxdata *mlxdata);
void initalise_camera_sphere(char **current_string, t_mlxdata *mlxdata);
void initalise_plane_cylinder(char **current_string, t_mlxdata *mlxdata);
void parse_line(char *src, t_mlxdata *mlxdata);             // parsing lines into the structs
int valid_parse(int argc, char **argv, t_mlxdata *mlxdata); // reading file and parsing into the struct

// in keyevent.c
int keyevent(int key, t_mlxdata *mlxdata);
void change_object(int key, t_mlxdata *mlxdata);
void change_light(int key, t_mlxdata *mlxdata);
void change_camera(int key, t_mlxdata *mlxdata);
void rotate(int key, t_mlxdata *mlxdata);

// in rotate_plane.c
float **create_rot_mat_x(float angle);
float **create_rot_mat_y(float angle);
float **create_rot_mat_z(float angle);
void rotate_x(float angle, t_mlxdata *mlxdata);
void rotate_y(float angle, t_mlxdata *mlxdata);
void rotate_z(float angle, t_mlxdata *mlxdata);
float *dot_product_plane(float **rot_mat, int *src_mat);


//colours
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define AMBIENT 0.1

#endif

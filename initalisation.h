#ifndef INITALISATION_H
#define INITALISATION_H

#include <unistd.h> // for read()
#include <fcntl.h>  // for open() and file-related constants
#include "./miniRT.h"

typedef struct s_sphere_values
{
    // sphere - sp
    float *sphere_xyz;
    float sphere_diameter;
    int *sphere_rgb;
}   t_sphere_values;

typedef struct s_plane_values
{
    // plane - pl
    float *plane_xyz;
    float *plane_norm_vect;
    int *plane_rgb;
}   t_plane_values;

typedef struct s_cylinder_values
{
    // cylinder - cy
    float *cylinder_xyz;
    float *cylinder_norm_vect;
    float cylinder_diameter;
    float cylinder_height;
    int *cylinder_rgb;
}   t_cylinder_values;

typedef struct s_inital_var
{
    int sphere_count;
    int plane_count;
    int cylinder_count;
    // Ambient light - A
    int Ambient_light_ratio;
    int *Ambient_lightning_rgb;
    // Cameral - C
    float *camera_xyz;
    float *camera_orientation;
    int camera_fov;
    // Light L
    float *light_xyz;
    int light_brightness;
    int *light_rgb;

    t_sphere_values *sphere_init;
    t_plane_values *plane_init;
    t_cylinder_values *cylinder_init;
}   t_inital_var;






#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tytang <tytang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:27:17 by tytang            #+#    #+#             */
/*   Updated: 2023/07/24 13:52:24 by tytang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int count_new_lines(char *src)
{
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    int lineCount = 0;

    // Open the file in read-only mode
    fd = open(src, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening the file");
        return 1;
    }

    // Read the file and count the number of lines
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        for (int i = 0; i < bytesRead; i++)
        {
            if (buffer[i] == '\n')
                lineCount++;
        }
    }

    if (bytesRead == -1)
    {
        perror("Error reading the file");
        return 1;
    }

    // Close the file
    close(fd);

    // Add one to the line count if the file doesn't end with a newline character
    if (buffer[bytesRead - 1] != '\n')
    {
        lineCount++;
    }

    return lineCount;
}

void initalise_lighting(char **current_string, t_mlxdata *mlxdata)
{
    if (ft_strcmp(current_string[0], "A") == 0)
    {
        printf("Ambient lightning, %s, %s\n", current_string[1], current_string[2]);
        mlxdata->initial_struct->Ambient_light_ratio = ft_atoi(current_string[1]);
        char **Ambient_lightning_rgb = ft_split(current_string[2], ',');
        int Ambient_lightning_rgb_int_arr[3];
        Ambient_lightning_rgb_int_arr[0] = ft_atoi(Ambient_lightning_rgb[0]);
        Ambient_lightning_rgb_int_arr[1] = ft_atoi(Ambient_lightning_rgb[1]);
        Ambient_lightning_rgb_int_arr[2] = ft_atoi(Ambient_lightning_rgb[2]);
        mlxdata->initial_struct->Ambient_lightning_rgb = Ambient_lightning_rgb_int_arr;
        printf("Ambient lightning rgb, %s, %s, %s\n",Ambient_lightning_rgb[0], Ambient_lightning_rgb[1], Ambient_lightning_rgb[2]);
    }
    else if (ft_strcmp(current_string[0], "L") == 0)
    {
        printf("Light, %s, %s, %s\n", current_string[1], current_string[2], current_string[3]);
        char **light_xyz = ft_split(current_string[1], ',');
        mlxdata->initial_struct->light_xyz[0] = (float)ft_atoi(light_xyz[0]);
        mlxdata->initial_struct->light_xyz[1] = (float)ft_atoi(light_xyz[1]);
        mlxdata->initial_struct->light_xyz[2] = (float)ft_atoi(light_xyz[2]);

        mlxdata->initial_struct->light_brightness = ft_atoi(current_string[2]);

        if (!current_string[3])
            return;
        char **light_rgb = ft_split(current_string[3], ',');
        mlxdata->initial_struct->light_rgb[0] = ft_atoi(light_rgb[0]);
        mlxdata->initial_struct->light_rgb[1] = ft_atoi(light_rgb[1]);
        mlxdata->initial_struct->light_rgb[2] = ft_atoi(light_rgb[2]);
    }
}

void initalise_camera_sphere(char **current_string, t_mlxdata *mlxdata)
{
    if (ft_strcmp(current_string[0], "C") == 0)
    {
        printf("Camera, %s, %s, %s\n", current_string[1], current_string[2], current_string[3]);
        char **camera_xyz_char = ft_split(current_string[1], ',');
        mlxdata->initial_struct->camera_xyz[0] = (float)ft_atoi(camera_xyz_char[0]);
        mlxdata->initial_struct->camera_xyz[1] = (float)ft_atoi(camera_xyz_char[1]);
        mlxdata->initial_struct->camera_xyz[2] = (float)ft_atoi(camera_xyz_char[2]);

        char **camera_orientation_char = ft_split(current_string[2], ',');
        mlxdata->initial_struct->camera_orientation[0] = (float)ft_atoi(camera_orientation_char[0]);
        mlxdata->initial_struct->camera_orientation[1] = (float)ft_atoi(camera_orientation_char[1]);
        mlxdata->initial_struct->camera_orientation[2] = (float)ft_atoi(camera_orientation_char[2]);
        mlxdata->initial_struct->camera_fov = ft_atoi(current_string[3]);
    }
    else if (ft_strcmp(current_string[0], "sp") == 0)
    {
        int current_sphere_idx;

        current_sphere_idx = mlxdata->initial_struct->sphere_count;
        mlxdata->initial_struct->sphere_init[current_sphere_idx].sphere_xyz = (float *)malloc(sizeof(float) * 3);
        mlxdata->initial_struct->sphere_init[current_sphere_idx].sphere_rgb = (int *)malloc(sizeof(int) * 3);
        
        
        printf("Sphere, %s, %s, %s\n", current_string[1], current_string[2], current_string[3]);
        char **sphere_xyz_char = ft_split(current_string[1], ',');
        float *sphere_xyz_float_arr = (float *)malloc(sizeof(float) * 3);
        sphere_xyz_float_arr[0] = (float)ft_atoi(sphere_xyz_char[0]);
        sphere_xyz_float_arr[1] = (float)ft_atoi(sphere_xyz_char[1]);
        sphere_xyz_float_arr[2] = (float)ft_atoi(sphere_xyz_char[2]);
        mlxdata->initial_struct->sphere_init[current_sphere_idx].sphere_xyz = sphere_xyz_float_arr;

        mlxdata->initial_struct->sphere_init[current_sphere_idx].sphere_diameter = (float)ft_atoi(current_string[2]);

        char **sphere_rgb_char = ft_split(current_string[3], ',');
        int *sphere_rgb_int_arr = (int *)malloc(sizeof(int) * 3);
        sphere_rgb_int_arr[0] = ft_atoi(sphere_rgb_char[0]);
        sphere_rgb_int_arr[1] = ft_atoi(sphere_rgb_char[1]);
        sphere_rgb_int_arr[2] = ft_atoi(sphere_rgb_char[2]);
        mlxdata->initial_struct->sphere_init[current_sphere_idx].sphere_rgb = sphere_rgb_int_arr;

        printf("mlxdata->initial_struct->sphere_init[%d].sphere_xyz[0]: %f\n", current_sphere_idx, mlxdata->initial_struct->sphere_init[current_sphere_idx].sphere_xyz[0]);
        printf("mlxdata->initial_struct->sphere_init[%d].sphere_xyz[1]: %f\n", current_sphere_idx, mlxdata->initial_struct->sphere_init[current_sphere_idx].sphere_xyz[1]);
        printf("mlxdata->initial_struct->sphere_init[%d].sphere_xyz[2]: %f\n", current_sphere_idx, mlxdata->initial_struct->sphere_init[current_sphere_idx].sphere_xyz[2]);

        printf("mlxdata->initial_struct->sphere_init[%d].sphere_rgb[0]: %d\n", current_sphere_idx, mlxdata->initial_struct->sphere_init[current_sphere_idx].sphere_rgb[0]);
        printf("mlxdata->initial_struct->sphere_init[%d].sphere_rgb[1]: %d\n", current_sphere_idx, mlxdata->initial_struct->sphere_init[current_sphere_idx].sphere_rgb[1]);
        printf("mlxdata->initial_struct->sphere_init[%d].sphere_rgb[2]: %d\n", current_sphere_idx, mlxdata->initial_struct->sphere_init[current_sphere_idx].sphere_rgb[2]);

        mlxdata->initial_struct->sphere_count++;

    }
}

void initalise_plane_cylinder(char **current_string, t_mlxdata *mlxdata)
{
    if (ft_strcmp(current_string[0], "pl") == 0)
    {
        int       current_plane_idx;

        current_plane_idx = mlxdata->initial_struct->plane_count;
        mlxdata->initial_struct->plane_init[current_plane_idx].plane_xyz = (float *)malloc(sizeof(float) * 3);
        mlxdata->initial_struct->plane_init[current_plane_idx].plane_norm_vect = (float *)malloc(sizeof(float) * 3);
        mlxdata->initial_struct->plane_init[current_plane_idx].plane_rgb = (int *)malloc(sizeof(int) * 3);


        printf("Plane, %s, %s, %s\n", current_string[1], current_string[2], current_string[3]);

        char **plane_xyz_char = ft_split(current_string[1], ',');
        float *plane_xyz_float_arr = (float *)malloc(sizeof(float) * 3);
        plane_xyz_float_arr[0] = (float)ft_atoi(plane_xyz_char[0]);
        plane_xyz_float_arr[1] = (float)ft_atoi(plane_xyz_char[1]);
        plane_xyz_float_arr[2] = (float)ft_atoi(plane_xyz_char[2]);
        mlxdata->initial_struct->plane_init[current_plane_idx].plane_xyz = plane_xyz_float_arr;

        char **plane_norm_vect_char = ft_split(current_string[2], ',');
        float *plane_norm_vect_float_arr = (float *)malloc(sizeof(float) * 3);
        plane_norm_vect_float_arr[0] = (float)ft_atoi(plane_norm_vect_char[0]);
        plane_norm_vect_float_arr[1] = (float)ft_atoi(plane_norm_vect_char[1]);
        plane_norm_vect_float_arr[2] = (float)ft_atoi(plane_norm_vect_char[2]);
        mlxdata->initial_struct->plane_init[current_plane_idx].plane_norm_vect = plane_norm_vect_float_arr;

        char **plane_rgb_char = ft_split(current_string[3], ',');
        int *plane_rgb_int_arr = (int *)malloc(sizeof(int) * 3);
        plane_rgb_int_arr[0] = ft_atoi(plane_rgb_char[0]);
        plane_rgb_int_arr[1] = ft_atoi(plane_rgb_char[1]);
        plane_rgb_int_arr[2] = ft_atoi(plane_rgb_char[2]);
        mlxdata->initial_struct->plane_init[current_plane_idx].plane_rgb = plane_rgb_int_arr;


        /*mlxdata->initial_struct->plane_init[current_plane_idx].plane_rgb[0] = ft_atoi(plane_rgb_char[0]);
        mlxdata->initial_struct->plane_init[current_plane_idx].plane_rgb[1] = ft_atoi(plane_rgb_char[1]);
        mlxdata->initial_struct->plane_init[current_plane_idx].plane_rgb[2] = ft_atoi(plane_rgb_char[2]);*/
        mlxdata->initial_struct->plane_count++;
    }
    else if (ft_strcmp(current_string[0], "cy") == 0)
    {
        int current_cylinder_idx;

        current_cylinder_idx = mlxdata->initial_struct->cylinder_count;

        mlxdata->initial_struct->cylinder_init[current_cylinder_idx].cylinder_xyz = (float *)malloc(sizeof(float) * 3);
        mlxdata->initial_struct->cylinder_init[current_cylinder_idx].cylinder_norm_vect = (float *)malloc(sizeof(float) * 3);
        mlxdata->initial_struct->cylinder_init[current_cylinder_idx].cylinder_rgb = (int *)malloc(sizeof(int) * 3);


        printf("Cylinder, %s, %s, %s, %s\n", current_string[1], current_string[2], current_string[3], current_string[4]);

        printf("Cylinder current_string[1]\n");
        char **cylinder_xyz_char = ft_split(current_string[1], ',');
        float *cylinder_xyz_float_arr = (float *)malloc(sizeof(float) * 3);
        cylinder_xyz_float_arr[0] = ft_atoi(cylinder_xyz_char[0]);
        cylinder_xyz_float_arr[1] = ft_atoi(cylinder_xyz_char[1]);
        cylinder_xyz_float_arr[2] = ft_atoi(cylinder_xyz_char[2]);
        mlxdata->initial_struct->cylinder_init[current_cylinder_idx].cylinder_xyz = cylinder_xyz_float_arr;

        printf("Cylinder current_string[2]\n");
        char **cylinder_norm_vect_char = ft_split(current_string[2], ',');
        float *cylinder_norm_vect_float_arr = (float *)malloc(sizeof(float) * 3);
        cylinder_norm_vect_float_arr[0] = (float)ft_atoi(cylinder_norm_vect_char[0]);
        cylinder_norm_vect_float_arr[1] = (float)ft_atoi(cylinder_norm_vect_char[1]);
        cylinder_norm_vect_float_arr[2] = (float)ft_atoi(cylinder_norm_vect_char[2]);
        mlxdata->initial_struct->cylinder_init[current_cylinder_idx].cylinder_norm_vect = cylinder_norm_vect_float_arr;


        printf("Cylinder current_string[3]\n");
        char **cylinder_diameter_char = ft_split(current_string[3], ',');
        mlxdata->initial_struct->cylinder_init[current_cylinder_idx].cylinder_diameter = (float)ft_atoi(current_string[3]);

        printf("Cylinder current_string[4]\n");
        //char **cylinder_height_char = ft_split(current_string[4], ',');
        mlxdata->initial_struct->cylinder_init[current_cylinder_idx].cylinder_height = (float)ft_atoi(current_string[4]);

        printf("Cylinder current_string[5]\n");
        char **cylinder_rgb_char = ft_split(current_string[5], ',');
        int *cylinder_rgb_int_arr = (int *)malloc(sizeof(int) * 3);
        cylinder_rgb_int_arr[0] = ft_atoi(cylinder_rgb_char[0]);
        cylinder_rgb_int_arr[1] = ft_atoi(cylinder_rgb_char[1]);
        cylinder_rgb_int_arr[2] = ft_atoi(cylinder_rgb_char[2]);
        mlxdata->initial_struct->cylinder_init[current_cylinder_idx].cylinder_rgb = cylinder_rgb_int_arr;
        /*mlxdata->initial_struct->cylinder_init[current_cylinder_idx].cylinder_rgb[0] = ft_atoi(cylinder_rgb_char[0]);
        mlxdata->initial_struct->cylinder_init[current_cylinder_idx].cylinder_rgb[1] = ft_atoi(cylinder_rgb_char[1]);
        mlxdata->initial_struct->cylinder_init[current_cylinder_idx].cylinder_rgb[2] = ft_atoi(cylinder_rgb_char[2]);*/

        mlxdata->initial_struct->cylinder_count++;
    }
}

// breaks down each line into inidividual arguments
void parse_line(char *src, t_mlxdata *mlxdata)
{
    char **current_string = ft_split(src, ' ');
    printf("current_string[0]: %s\n", current_string[0]);
    if ((ft_strcmp(current_string[0], "A") == 0) || (ft_strcmp(current_string[0], "L") == 0)){
        printf("inside initalise_lighting\n");
        initalise_lighting(current_string, mlxdata);
    }
        
    else if ((ft_strcmp(current_string[0], "C") == 0) || (ft_strcmp(current_string[0], "sp") == 0)){
        printf("inside initalise_camera_sphere\n");
        initalise_camera_sphere(current_string, mlxdata);
    }
    else if ((ft_strcmp(current_string[0], "pl") == 0) || (ft_strcmp(current_string[0], "cy") == 0)){
        printf("inside initalise_plane_cylinder\n");
        initalise_plane_cylinder(current_string, mlxdata);
    }
        
}

// reading and parsing
int valid_parse(int argc, char **argv, t_mlxdata *mlxdata)
{
    {
        mlxdata->initial_struct->sphere_count = 0;
        mlxdata->initial_struct->plane_count = 0;
        mlxdata->initial_struct->cylinder_count = 0;

        printf("second arg: %s\n", argv[1]);
        char *filename = argv[1];
        //printf("second arg: %s\n", filename);
        printf("successful file open\n");

        int fd = open(filename, O_RDONLY);
        if (fd == -1)
            printf("failed to open\n");

        int line_count = count_new_lines(argv[1]);

        char buffer[1024];
        ssize_t bytesRead;

        fd = open(filename, O_RDONLY);
        int i = 0;
        printf("line_count: %d\n", line_count);

        mlxdata->initial_struct->sphere_init = malloc(sizeof(t_sphere_values) * 100);
        mlxdata->initial_struct->plane_init = malloc(sizeof(t_plane_values) * 100);
        mlxdata->initial_struct->cylinder_init = malloc(sizeof(t_cylinder_values) * 100);

        while (i < line_count)
        {
            printf("i: %d\n", i);
            char *current_string = get_next_line(fd);
            if (current_string[0] == '\n' || current_string[ft_strlen(current_string)-1] == EOF || !current_string)
                break;
            printf("valid_parse while loop\n");
            parse_line(current_string, mlxdata);
            i++;
        }

        if (bytesRead == -1)
        {
            printf("Error reading the file");
            return -1;
        }



        printf("(valid_parse) mlxdata->initial_struct->sphere_count: %d\n", mlxdata->initial_struct->sphere_count);
        printf("(valid_parse) mlxdata->initial_struct->plane_count: %d\n", mlxdata->initial_struct->plane_count);
        printf("(valid_parse) mlxdata->initial_struct->cylinder_count: %d\n", mlxdata->initial_struct->cylinder_count);

        for (int i = 0; i < (int)mlxdata->initial_struct->sphere_count; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("(valid_parse sphere) mlxdata->initial_struct->sphere_init[%d].sphere_rgb[%d]: %d\n", i, j, mlxdata->initial_struct->sphere_init[i].sphere_rgb[j]);
                printf("(valid_parse sphere) mlxdata->initial_struct->sphere_init[%d].sphere_xyz_char[%d]: %f\n", i, j, mlxdata->initial_struct->sphere_init[i].sphere_xyz[j]);
            }
        }

        for (int i = 0; i < (int)mlxdata->initial_struct->plane_count; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("(valid_parse plane) mlxdata->initial_struct->plane_init[%d].plane_rgb[%d]: %d\n", i, j, mlxdata->initial_struct->plane_init[i].plane_rgb[j]);
                printf("(valid_parse plane) mlxdata->initial_struct->plane_init[%d].plane_xyz[%d]: %f\n", i, j, mlxdata->initial_struct->plane_init[i].plane_xyz[j]);
                printf("(valid_parse plane) mlxdata->initial_struct->plane_init[%d].plane_norm_vect[%d]: %f\n", i, j, mlxdata->initial_struct->plane_init[i].plane_norm_vect[j]);
            }
        }

        for (int i = 0; i < (int)mlxdata->initial_struct->cylinder_count; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("(valid_parse cylinder) mlxdata->initial_struct->cylinder_init[%d].cylinder_rgb[%d]: %d\n", i, j, mlxdata->initial_struct->cylinder_init[i].cylinder_rgb[j]);
                printf("(valid_parse cylinder) mlxdata->initial_struct->cylinder_init[%d].cylinder_xyz[%d]: %f\n", i, j, mlxdata->initial_struct->cylinder_init[i].cylinder_xyz[j]);
                printf("(valid_parse cylinder) mlxdata->initial_struct->cylinder_init[%d].cylinder_norm_vect[%d]: %f\n", i, j, mlxdata->initial_struct->cylinder_init[i].cylinder_norm_vect[j]);
                printf("(valid_parse cylinder) mlxdata->initial_struct->cylinder_init[%d].cylinder_diameter: %f\n", i, mlxdata->initial_struct->cylinder_init[i].cylinder_diameter);
                printf("(valid_parse cylinder) mlxdata->initial_struct->cylinder_init[%d].cylinder_height: %f\n", i, mlxdata->initial_struct->cylinder_init[i].cylinder_height);
            }
        }

        close(fd);
        printf("successful file closure\n");
    }

    return 0;
}


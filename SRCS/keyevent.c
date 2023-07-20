#include "../miniRT.h"

int keyevent(int key, t_mlxdata *mlxdata)
{
    if (key == KEY_ESCAPE)
        exit(0);
    if ((key == KEY_ANSI_A) || (key == KEY_ANSI_D) || (key == KEY_ANSI_W) || (key == KEY_ANSI_S))
    {
        // wasd = object movement
        change_object(key, mlxdata);
    }
    if ((key == KEY_ANSI_J) || (key == KEY_ANSI_L) || (key == KEY_ANSI_I) || (key == KEY_ANSI_K))
    {
        // ijkl = lights movement
        change_light(key, mlxdata);
    }

    if ((key == KEY_LEFT) || (key == KEY_RIGHT) || (key == KEY_UP) || (key == KEY_DOWN))
    {
        // up, down, left right = camera movement
        change_camera(key, mlxdata);
    }

    if ((key == KEY_ANSI_Z) || (key == KEY_ANSI_X) || (key == KEY_ANSI_C) || (key == KEY_ANSI_V)
        || (key == KEY_ANSI_B) || (key == KEY_ANSI_N))
    {
        //z = rotate x axis clockwise, x = rotate x axis anticlockwise
        //c = rotate y axis clockwise, v = rotate y axis anticlockwise
        //b = rotate z axis clockwise, n = rotate z axis anticlockwise
        rotate(key, mlxdata);
    }

    miniRT(mlxdata);
    return (1);
}

void change_object(int key, t_mlxdata *mlxdata)
{
    if (key == KEY_ANSI_A)
    {
        if (mlxdata->initial_struct->sphere_count > 0)
            mlxdata->initial_struct->sphere_init->sphere_xyz[0] -= 1;
        if (mlxdata->initial_struct->plane_count > 0)
            mlxdata->initial_struct->plane_init->plane_xyz[0] -= 1;
        if (mlxdata->initial_struct->cylinder_count > 0)
            mlxdata->initial_struct->cylinder_init->cylinder_xyz[0] -= 1;
    }
    else if (key == KEY_ANSI_D)
    {
        if (mlxdata->initial_struct->sphere_count > 0)
            mlxdata->initial_struct->sphere_init->sphere_xyz[0] += 1;
        if (mlxdata->initial_struct->plane_count > 0)
            mlxdata->initial_struct->plane_init->plane_xyz[0] += 1;
        if (mlxdata->initial_struct->cylinder_count > 0)
            mlxdata->initial_struct->cylinder_init->cylinder_xyz[0] += 1;
    }
    else if (key == KEY_ANSI_W)
    {
        if (mlxdata->initial_struct->sphere_count > 0)
            mlxdata->initial_struct->sphere_init->sphere_xyz[1] -= 1;
        if (mlxdata->initial_struct->plane_count > 0)
            mlxdata->initial_struct->plane_init->plane_xyz[1] -= 1;
        if (mlxdata->initial_struct->cylinder_count > 0)
            mlxdata->initial_struct->cylinder_init->cylinder_xyz[1] -= 1;
    }
    else if (key == KEY_ANSI_S)
    {
        if (mlxdata->initial_struct->sphere_count > 0)
            mlxdata->initial_struct->sphere_init->sphere_xyz[1] += 1;
        if (mlxdata->initial_struct->plane_count > 0)
            mlxdata->initial_struct->plane_init->plane_xyz[1] += 1;
        if (mlxdata->initial_struct->cylinder_count > 0)
            mlxdata->initial_struct->cylinder_init->cylinder_xyz[1] += 1;
    }
}

void change_light(int key, t_mlxdata *mlxdata)
{
    if (key == KEY_ANSI_J)
    {
        mlxdata->initial_struct->light_xyz[0] -= 1;
    }
    else if (key == KEY_ANSI_L)
    {
        mlxdata->initial_struct->light_xyz[0] += 1;
    }
    else if (key == KEY_ANSI_I)
    {
        mlxdata->initial_struct->light_xyz[1] -= 1;
    }
    else if (key == KEY_ANSI_K)
    {
        mlxdata->initial_struct->light_xyz[1] += 1;
    }
}

void change_camera(int key, t_mlxdata *mlxdata)
{
    if (key == KEY_LEFT)
    {
        mlxdata->initial_struct->camera_xyz[0] -= 1;
    }
    else if (key == KEY_RIGHT)
    {
        mlxdata->initial_struct->camera_xyz[0] += 1;
    }
    else if (key == KEY_UP)
    {
        mlxdata->initial_struct->camera_xyz[1] -= 1;
    }
    else if (key == KEY_DOWN)
    {
        mlxdata->initial_struct->camera_xyz[1] += 1;
    }
}

void rotate(int key, t_mlxdata *mlxdata)
{
    if ((key == KEY_ANSI_Z) || (key == KEY_ANSI_X))
    {
        //z = rotate x axis clockwise, x = rotate x axis anticlockwise
        if (key == KEY_ANSI_Z)
            rotate_x(5, mlxdata);
        else if (key == KEY_ANSI_X)
            rotate_x(-5, mlxdata);
    }
    else if ((key == KEY_ANSI_C) || (key == KEY_ANSI_V))
    {
        //c = rotate y axis clockwise, v = rotate y axis anticlockwise
        if (key == KEY_ANSI_C)
            rotate_y(5, mlxdata);
        else if (key == KEY_ANSI_X)
            rotate_y(-5, mlxdata);
    }
    else if ((key == KEY_ANSI_B) || (key == KEY_ANSI_N))
    {
        //b = rotate z axis clockwise, n = rotate z axis anticlockwise
        if (key == KEY_ANSI_B)
            rotate_z(5, mlxdata);
        else if (key == KEY_ANSI_N)
            rotate_z(-5, mlxdata);
    }
}


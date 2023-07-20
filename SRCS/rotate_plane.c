#include "../miniRT.h"

float **create_rot_mat_x(float angle)
{
    float cosA = cos(angle);
    float sinA = sin(angle);

    float **rot_mat_x = (float **)malloc(3*sizeof(float *));
    int i = 0;
    while (i < 3)
    {
        rot_mat_x[i] = (float *)malloc(3*sizeof(float));
        i++;
    }
    rot_mat_x[0][0] = 1;
    rot_mat_x[0][1] = 0;
    rot_mat_x[0][2] = 0;
    rot_mat_x[1][0] = 0;
    rot_mat_x[1][1] = cosA;
    rot_mat_x[1][2] = -sinA;
    rot_mat_x[2][0] = 0;
    rot_mat_x[2][1] = sinA;
    rot_mat_x[2][2] = cosA;

    return rot_mat_x;
}

float **create_rot_mat_y(float angle)
{
    float cosA = cos(angle);
    float sinA = sin(angle);

    float **rot_mat_y = (float **)malloc(3*sizeof(float *));
    int i = 0;
    while (i < 3)
    {
        rot_mat_y[i] = (float *)malloc(3*sizeof(float));
        i++;
    }
    rot_mat_y[0][0] = cosA;
    rot_mat_y[0][1] = 0;
    rot_mat_y[0][2] = sinA;
    rot_mat_y[1][0] = 0;
    rot_mat_y[1][1] = 1;
    rot_mat_y[1][2] = 0;
    rot_mat_y[2][0] = -sinA;
    rot_mat_y[2][1] = 0;
    rot_mat_y[2][2] = cosA;

    return rot_mat_y;
}

float **create_rot_mat_z(float angle)
{
    float cosA = cos(angle);
    float sinA = sin(angle);

    float **rot_mat_z = (float **)malloc(3*sizeof(float *));
    int i = 0;
    while (i < 3)
    {
        rot_mat_z[i] = (float *)malloc(3*sizeof(float));
        i++;
    }
    rot_mat_z[0][0] = cosA;
    rot_mat_z[0][1] = -sinA;
    rot_mat_z[0][2] = 0;
    rot_mat_z[1][0] = sinA;
    rot_mat_z[1][1] = cosA;
    rot_mat_z[1][2] = 0;
    rot_mat_z[2][0] = 0;
    rot_mat_z[2][1] = 0;
    rot_mat_z[2][2] = 1;

    return rot_mat_z;
}

void rotate_x(float angle, t_mlxdata *mlxdata)
{
    float **rotation_matrix_x = create_rot_mat_x(angle);

    int plane_count = mlxdata->initial_struct->plane_count;
    int ctr = 0;
    while (ctr < plane_count)
    {
        mlxdata->initial_struct->plane_init[ctr].plane_norm_vect = dot_product_plane(rotation_matrix_x, mlxdata->initial_struct->plane_init[ctr].plane_norm_vect);
        ctr++;
    }
}

void rotate_y(float angle, t_mlxdata *mlxdata)
{
    float **rotation_matrix_y = create_rot_mat_x(angle);

    int plane_count = mlxdata->initial_struct->plane_count;
    int ctr = 0;
    while (ctr < plane_count)
    {
        mlxdata->initial_struct->plane_init[ctr].plane_norm_vect = dot_product_plane(rotation_matrix_y, mlxdata->initial_struct->plane_init[ctr].plane_norm_vect);
        ctr++;
    }
}

void rotate_z(float angle, t_mlxdata *mlxdata)
{
    float **rotation_matrix_z = create_rot_mat_x(angle);

    int plane_count = mlxdata->initial_struct->plane_count;
    int ctr = 0;
    while (ctr < plane_count)
    {
        mlxdata->initial_struct->plane_init[ctr].plane_norm_vect = dot_product_plane(rotation_matrix_z, mlxdata->initial_struct->plane_init[ctr].plane_norm_vect);
        ctr++;
    }
}

float *dot_product_plane(float **rot_mat, float *src_mat)
{
    float r_height = 3;
    float r_width = 3;
    float src_height = 3;
    float src_width = 1;

    float *final_result = (float *)malloc(3*sizeof(float));
    final_result[0] = rot_mat[0][0] * src_mat[0] + rot_mat[0][1] * src_mat[0] + rot_mat[0][2] * (float)src_mat[0];
    final_result[1] = rot_mat[1][0] * src_mat[1] + rot_mat[1][1] * src_mat[1] + rot_mat[1][2] * (float)src_mat[1];
    final_result[2] = rot_mat[2][0] * src_mat[2] + rot_mat[2][1] * src_mat[2] + rot_mat[2][2] * (float)src_mat[2];

    return final_result;
}

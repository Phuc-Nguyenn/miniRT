/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:25:24 by phunguye          #+#    #+#             */
/*   Updated: 2023/07/07 17:20:51 by phunguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "./libftprintf/ft_printf.h"
# include "./minilibx/mlx.h"
# include "./get_next_line/get_next_line.h"

# define W_WIDTH 1920
# define W_HEIGHT 1080

typedef struct s_vector
{
	float x;
	float y;
	float z;
	int alpha;
} t_vector;

typedef struct ray
{
	t_vector start_position;
	t_vector direction;
	float magnitude;
} t_ray;

typedef struct camera
{
	t_vector view_point;
	t_vector orientation;
	t_vector *viewport;
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

//ft_pixelput.c
void	ft_pixelput(t_mlxdata *mlxdata, int x, int y, int colour);
void	ft_translatedput(t_mlxdata *mlxdata, int x, int y, int colour);

//main.c
int initialise_mlx(t_mlxdata *mlxdata);

//image.c
void	clear_screen(t_mlxdata *mlxdata);

//vector_operations.c
t_vector set_vct(float x, float y, float z, float alpha);
t_vector vct_add(t_vector vct1, t_vector vct2);
t_vector vct_subtract(t_vector vct1, t_vector vct2);
t_vector vct_scalar_prod(t_vector vct1, int scalar);
t_vector vct_cross_prod(t_vector vct1, t_vector vct2);


//colours
# define WHITE 0xFFFFFF
# define BLACK 0x000000

#endif
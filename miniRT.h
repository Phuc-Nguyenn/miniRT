#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./minilibx/mlx.h"

typedef struct s_mlxdata
{
	void	*mlx_ptr;
	void	*wdw_ptr;
	void	*img_ptr;
	char	*string;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_mlxdata;


#endif
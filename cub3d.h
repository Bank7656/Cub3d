#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>

# include "libft.h"
# include "MLX42.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define FOV 60 * (M_PI / 180)

# define TILE_SIZE 32
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

typedef struct  s_player {
    int     x;
    int     y;
    char    direction;
} t_player;

typedef struct  s_cub3d {
    mlx_t       *mlx;
    mlx_image_t *image;
    t_player    player;

}   t_cub3d;



int     init_data(t_cub3d *data);

#endif

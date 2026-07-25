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


# define RES 4
# define NUMBER_RAYS 5 * TILE_SIZE / RES 

# define RADIUS 3

typedef struct  s_player {
    int     x;
    int     y;
    char    direction;
    int     radius;
} t_player;

typedef struct  s_cub3d {
    mlx_t       *mlx;
    mlx_image_t *image;
    t_player    player;

}   t_cub3d;



int     init_data(t_cub3d *data);
void    init_player(t_cub3d *data, char map[5][5]);


int     is_player_direction(char c);

#endif

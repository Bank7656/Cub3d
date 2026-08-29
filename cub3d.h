#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define FOV 60 * (M_PI / 180)

# define TILE_SIZE 32
# define WIDTH 1280
# define HEIGHT 720


# define RES 4
# define NUMBER_RAYS 5 * TILE_SIZE / RES 

# define RADIUS 3

typedef struct s_vec {
    double     x;
    double     y;
} t_vec;

typedef struct s_player {
    t_vec   pos;
    t_vec   dir;
    t_vec   plane;
} t_player;

typedef struct s_ray {
    t_vec   dir;            /* this column's ray direction     */
    t_vec   delta_dist;     /* ray length per grid line        */
    t_vec   side_dist;      /* ray length to next grid line    */
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    int     side;           /* 0 = vertical face, 1 = horizontal */
    int     hit;
    double  perp_wall_dist;
    int     line_height;
    int     draw_start;
    int     draw_end;
}   t_ray;

typedef struct s_game {
    mlx_t       *mlx;
    mlx_image_t *img;
    char        **map;
    int         map_width;
    int         map_height;
    t_player    player;
    uint32_t    floor;
    uint32_t    ceiling;
} t_game;


int     init_player(t_game *g);
void    init_ray(t_game *g, t_ray *r, int x);


void draw_background(t_game *g);
void draw_column(t_game *g, t_ray *r, int x);

void frame(void *param);
void handle_input(t_game *g);

void on_key(mlx_key_data_t key, void *param);


char    **dup_map(char **src);
void    free_map(char **arr);


#endif

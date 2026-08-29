#include "cub3d.h"

static char *g_map[] = {
    "111111",
    "100101",
    "101001",
    "1100N1",
    "111111",
    NULL
};


static void frame(void *param);
static void on_key(mlx_key_data_t key, void *param);

static void handle_input(t_game *g);
static void try_move(t_game *g, double dx, double dy);
static double margin(double d, double m);
static int is_walkable(t_game *g, double x, double y);


static void run_dda(t_game *g, t_ray *r);
static void render_column(t_game *g, int x);
static void set_wall_bounds(t_ray *r);

int main(void)
{
    t_game  g;

    // Init constant 
    g.map = dup_map(g_map);
    g.map_width = 6;
    g.map_height = 5;
    g.ceiling = 0x87CEEBFF;
    g.floor = 0x5A4632FF;
    //

    if (!init_player(&g))
    {
        printf("Error\n");
        return (EXIT_FAILURE);
    }

    g.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
    if (!g.mlx)
        return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
    g.img = mlx_new_image(g.mlx, WIDTH, HEIGHT);
    if (!g.img || mlx_image_to_window(g.mlx, g.img, 0, 0) == -1)
        return (mlx_close_window(g.mlx), EXIT_FAILURE);


    mlx_loop_hook(g.mlx, frame, &g);
    mlx_key_hook(g.mlx, on_key, &g);
    mlx_loop(g.mlx);
    mlx_terminate(g.mlx);
    return (EXIT_SUCCESS);
}

static void frame(void *param)
{
    int     x;
    t_game *g;

    g = (t_game *)param;
    draw_background(g);
    handle_input(g);
    x = 0;
    while (x < WIDTH)
    {
        render_column(g, x);
        x++;
    }
}

static void handle_input(t_game *g)
{
    double  speed;
    double  rot;

    speed = 0.05;
    rot = 2;
    if (mlx_is_key_down(g->mlx, MLX_KEY_W))
        try_move(g, g->player.dir.x * speed, g->player.dir.y * speed);
    if (mlx_is_key_down(g->mlx, MLX_KEY_S))
        try_move(g, -g->player.dir.x * speed, -g->player.dir.y * speed);
    if (mlx_is_key_down(g->mlx, MLX_KEY_A))
        try_move(g, -g->player.plane.x * speed, -g->player.plane.y * speed);
    if (mlx_is_key_down(g->mlx, MLX_KEY_D))
        try_move(g, g->player.plane.x * speed, g->player.plane.y * speed);

}

static void try_move(t_game *g, double dx, double dy)
{
    t_vec   *pos;

    pos = &g->player.pos;
    if (is_walkable(g, pos->x + dx + margin(dx, 0.2), pos->y))
        pos->x += dx;
    if (is_walkable(g, pos->x, pos->y + dy + margin(dy, 0.2)))
        pos->y += dy;
}

static int is_walkable(t_game *g, double x, double y)
{
    if (x < 0 || y < 0 || x >= g->map_width || y >= g->map_height)
        return (0);
    if (g->map[(int)y][(int)x] != '1')
        return (1);
    return (0);
}

static double margin(double d, double m)
{
    if (d > 0)
        return (m);
    if (d < 0)
        return (-m);
    else
        return (0);
}

static void render_column(t_game *g, int x)
{
    t_ray   ray;

    init_ray(g, &ray, x);
    run_dda(g, &ray);
    draw_column(g, &ray, x);
}

static void run_dda(t_game *g, t_ray *r)
{
    while (!r->hit)
    {
        if (r->side_dist.x < r->side_dist.y)
        {
            r->side_dist.x += r->delta_dist.x;
            r->map_x += r->step_x;
            r->side = 0;
        }
        else
        {
            r->side_dist.y += r->delta_dist.y;
            r->map_y += r->step_y;
            r->side = 1;
        }
        if (g->map[r->map_y][r->map_x] == '1')
            r->hit = 1;
    }
}

static void on_key(mlx_key_data_t key, void *param)
{
    if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
        mlx_close_window(((t_game *)param) -> mlx);
}

#include "cub3d.h"

typedef struct  s_cub3d{
    mlx_t       *mlx;
    mlx_image_t *image;

}   t_cub3d;


int     init_data(t_cub3d *data);
void    map_render(t_cub3d *data, int map[5][5]);

int main(void)
{
    t_cub3d data;

    int map[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };

    init_data(&data);

    map_render(&data, map);

    mlx_loop(data.mlx);
    return (EXIT_SUCCESS);
}

void    map_render(t_cub3d *data, int map[5][5])
{
    uint32_t color;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%i", map[i][j]);
            if (j != 4)
                printf(" ");
            if (map[i][j] == 1)
                color = 0xFF0000FF;
            else
                color = 0xFFFFFFFF;
            for (int k=0; k < TILE_SIZE; k++)
            {
                for (int l=0; l < TILE_SIZE; l++)
                {
                    mlx_put_pixel(
                        data->image,
                        (i * TILE_SIZE) + k,
                        (j * TILE_SIZE) + l,
                    color);
                }
            }
        }
        printf("\n");
    }
}

int init_data(t_cub3d *data)
{
    int rows = 5;
    int cols = 5;
    int window_width = rows * TILE_SIZE;
    int window_height = cols * TILE_SIZE;
    data->mlx = mlx_init(window_width, window_height, "Cub3d", false);
    if (!data->mlx)
        return (1);
    //mlx_set_window_limit(data->mlx, 1024, 768, -1, -1);
    data->image = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	if (data->image == NULL)
        return (1);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
        return (1);

    return (0);
}

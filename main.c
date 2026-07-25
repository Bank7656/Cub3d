#include "cub3d.h"

void    map_render(t_cub3d *data, char map[5][5]);
void    check_hook(t_cub3d *data);
void	my_keyhook(mlx_key_data_t keydata, void *param);

char map[5][5] = {
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '0', '1'},
        {'1', '0', 'N', '0', '1'},
        {'1', '0', '0', '0', '1'},
        {'1', '1', '1', '1', '1'}
    };

int main(void)
{
    t_cub3d data;

    init_data(&data);

    map_render(&data, map);
    init_player(&data, map);

    // Start Debug
    printf("FOV: %f\n", FOV);
    printf("Player Position: x=%i, y=%i\n", data.player.x, data.player.y);
    // End Debug

    check_hook(&data);
    mlx_loop(data.mlx);

    return (EXIT_SUCCESS);
}

void    check_hook(t_cub3d *data)
{
    mlx_key_hook(data->mlx, &my_keyhook, data);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
    t_cub3d *data;

    data = (t_cub3d *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

void    map_render(t_cub3d *data, char map[5][5])
{
    uint32_t color;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%c", map[i][j]);
            if (j != 4)
                printf(" ");
            if (map[i][j] == '1')
                color = 0xFF0000FF;
            else if (map[i][j] == 'N')
                color = 0x00FF00FF;
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
                        color
                    );
                }
            }
        }
        printf("\n");
    }
}


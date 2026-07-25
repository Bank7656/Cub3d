#include "cub3d.h"

void    map_render(t_cub3d *data, char map[5][5]);
void    init_player(t_cub3d *data, char map[5][5]);

int main(void)
{
    t_cub3d data;

    char map[5][5] = {
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '0', '1'},
        {'1', '0', 'N', '0', '1'},
        {'1', '0', '0', '0', '1'},
        {'1', '1', '1', '1', '1'}
    };

    init_data(&data);

    map_render(&data, map);
    init_player(&data, map);

    // Start Debug
    printf("FOV: %f\n", FOV);
    printf("Player Position: x=%i, y=%i\n", data.player.x, data.player.y);
    // End Debug

    //mlx_loop(data.mlx);

    return (EXIT_SUCCESS);
}

int     is_player_direction(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (1);
    return (0);
}

void    init_player(t_cub3d *data, char map[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (is_player_direction(map[i][j]))
            {
                data->player.x = i;
                data->player.y = j;
                data->player.direction = map[i][j];
                return ;
            }
        }
    }
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


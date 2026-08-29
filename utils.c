#include "cub3d.h"

char **dup_map(char **src)
{
    char    **dst;
    int     i;

    i = 0;
    while (src[i])
        i++;
    dst = ft_calloc(i + 1, sizeof(char *));
    if (!dst)
        return (NULL);
    i = 0;
    while (src[i])
    {
        dst[i] = ft_strdup(src[i]);
        if (!dst[i])
            return (free_map(dst), NULL);
        i++;
    }
    return (dst);
}

void    free_map(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr);
        i++;
    }
    free(arr);
}

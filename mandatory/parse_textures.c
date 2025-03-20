#include "cub.h"

void set_texture(t_data *data, char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;

    if (ft_strncmp(line, "NO ", 3) == 0)
    {
        data->NO = extract_content(line + 2);
        data->order.NO_line = data->order.line_order;
    }
    else if (ft_strncmp(line, "SO ", 3) == 0)
    {
        data->SO = extract_content(line + 2);
        data->order.SO_line = data->order.line_order;
    }
    else if (ft_strncmp(line, "EA ", 3) == 0)
    {
        data->EA = extract_content(line + 2);
        data->order.EA_line = data->order.line_order;
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
        data->WE = extract_content(line + 2);
        data->order.WE_line = data->order.line_order;
    }
}



mlx_texture_t *load_texutes(char *path)
{
    mlx_texture_t *texture;
    texture = mlx_load_png(path);
    if (!texture)
        ft_error('t');
    return (texture);
}

void load_all_text(t_data *data)
{
    data->north = load_texutes(data->NO);
    data->south = load_texutes(data->SO);
    data->east = load_texutes(data->EA);
    data->west = load_texutes(data->WE);
}

mlx_texture_t *get_wall_texture(t_data *data)
{
    if (data->side_wall == 0)
    {
        if (data->ray.rayd_x > 0)
            return data->east;
        else
            return data->west;
    }
    else
    {
        if (data->ray.rayd_y > 0)
            return data->south;
        else
            return data->north;
    }
}

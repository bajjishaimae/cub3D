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
/*
north 1
south 2
east 3
west 4
*/

// void fill_text(t_data *data, int i)
// {
//     int y = 0;
//     int x = 0;

//     if (i == 0)
//     {
//         data->textures = c_malloc(sizeof(int *) * 4, 1);
//         if (!data->textures)
//             ft_error('a');
//     }

//     int tex_size = data->text[i].width * data->text[i].height;
//     data->textures[i] = c_malloc(sizeof(int) * tex_size, 1);
//     if (!data->textures[i])
//         ft_error('a');

//     while (y < data->text[i].height)
//     {
//         x = 0;
//         while (x < data->text[i].width)
//         {
//             int pixel_offset = (y * data->text[i].line_len) + (x * (data->text[i].bpp / 8));
//             int color = *(int *)(data->text[i].addr + pixel_offset);
//             data->textures[i][y * data->text[i].width + x] = color;
//             x++;
//         }
//         y++;
//     }    
// }

mlx_texture_t *get_wall_texture(t_data *data)
{
    if (data->side_wall == 1)
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
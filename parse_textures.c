#include "cub.h"
#include "minilibx-linux/mlx.h"

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


// t_text load_texutes(char *path)
// {
//     t_text texture;
//     // texture.img = mlx_xpm_file_to_image(mlx, path, &texture.width, &texture.height);
//     if (texture.img == NULL)
//         ft_error('t');
//     texture.addr = mlx_get_data_addr(texture.img, &texture.bpp, &texture.line_len, &texture.endian);
//     return (texture);
// }

// void load_all_text(t_data *data)
// {
//     data->north = load_texutes(data->NO);
//     data->south = load_texutes(data->SO);
//     data->east = load_texutes(data->EA);
//     data->west = load_texutes(data->WE);
// }


// void destroy_text(t_data *data)
// {
// //     mlx_destroy_image(data->mlx, data->north.img);
// //     mlx_destroy_image(data->mlx, data->south.img);
// //     mlx_destroy_image(data->mlx, data->east.img);
// //     mlx_destroy_image(data->mlx, data->west.img);
// }
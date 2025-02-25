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


t_text load_texutes(char *path, t_data *data)
{
    t_text texture;
    texture.img = mlx_xpm_file_to_image(data->mlx_ptr, path, &texture.width, &texture.height);
    if (texture.img == NULL)
        ft_error('t');
    texture.addr = mlx_get_data_addr(texture.img, &texture.bpp, &texture.line_len, &texture.endian);
    return (texture);
}

void load_all_text(t_data *data)
{
    int i = 0;
    data->text[0] = load_texutes(data->NO, data);
    data->text[1] = load_texutes(data->SO, data);
    data->text[2] = load_texutes(data->EA, data);
    data->text[3] = load_texutes(data->WE, data);
    while (i < 4)
    {
        fill_text(data, i);
        i++;
    }
}


// void destroy_text(t_data *data)
// {
//     mlx_destroy_image(data->mlx_ptr, data->north.img);
//     mlx_destroy_image(data->mlx_ptr, data->south.img);
//     mlx_destroy_image(data->mlx_ptr, data->east.img);
//     mlx_destroy_image(data->mlx_ptr, data->west.img);
// }

int get_wall_texture(t_data *data, int side, double rayd_x, double rayd_y)
{
    if (side == 0)
    {
        if (rayd_x > 0) 
            return 2;
        else 
            return 3;
    }
    else
    {
        if (rayd_y > 0) 
            return 1;
        else 
            return 0;
    }
}

/*
north 1
south 2
east 3
west 4
*/

void fill_text(t_data *data, int i)
{

    int y = 0;
    int x = 0;
    if (i == 0)
    {
        data->textures = c_malloc(sizeof(int *) * 4, 1);
        if (!data->textures)
            ft_error('a');
    }

    data->textures[i] = c_malloc(sizeof(int) * (data->text[i].height * data->text[i].width), 1);
    
    while (y < data->text[i].height)
    {
        x = 0;
        while (x < data->text[i].width)
        {
            data->textures[i][data->text[i].height * y + x] = data->text[i].addr[data->text[i].height * y + x];
            x++;
        }
        y++;
    }    
}
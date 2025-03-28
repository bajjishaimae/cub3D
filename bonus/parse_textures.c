#include "cub.h"

void	set_texture(t_data *data, char *line)
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
	else if (ft_strncmp(line, "D ", 2) == 0)
	{
		data->DO = extract_content(line + 1);
		data->order.DO_line = data->order.line_order;
	}
	else if (ft_strncmp(line, "SP ", 3) == 0)
	{
		data->SP = extract_content(line + 2);
		data->order.SP_line = data->order.line_order;
	}
}

mlx_texture_t	*load_texutes(char *path)
{
	mlx_texture_t *texture;

	texture = mlx_load_png(path);
	if (!texture)
		ft_error('t');
	return (texture);
}

void	load_frames(t_data *data)
{
	int	i;
	char	*s;
	char	*path;

	path = malloc(sizeof(char) * (50));
	if (!path)
	{
		printf("Memory allocation error!\n");
		return;
	}
	i = 1;
	while (i <= 28)
	{
		s = ft_itoa(i);
		path = ft_strjoin("textures/weapon/", ft_strjoin(s, ".png"));
		data->frames[i - 1] = load_texutes(path);
		i++;
	}
}

void	load_all_text(t_data *data)
{
	data->north = load_texutes(data->NO);
	data->south = load_texutes(data->SO);
	data->east = load_texutes(data->EA);
	data->west = load_texutes(data->WE);
	data->door = load_texutes(data->DO);
	data->sprite = load_texutes(data->SP);
}

mlx_texture_t	*get_wall_texture(t_data *data)
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
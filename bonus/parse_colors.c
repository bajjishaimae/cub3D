#include "cub.h"

int check_content(char *colors)
{
	int i;

	i = 0;
	while(colors && colors[i])
	{
		if (colors[i] != ' ' && colors[i] != '\n' && colors[i] != '\t' && colors[i] != ',' && !ft_isdigit(colors[i]))
			return (0);
		i++;
	}
	return (1);
}

static int* select_color_array(t_data *data, char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    
    if (ft_strncmp(line, "F ", 2) == 0)
    {
        data->order.F_line = data->order.line_order;
        return data->floor_color;
    }
    else if (ft_strncmp(line, "C ", 2) == 0)
    {
        data->order.C_line = data->order.line_order;
        return data->ceiling_color;
    }
    return NULL;
}

static void parse_color_values(int *color_array, char *colors)
{
    char **splited;
    int i = 0;

    if (!check_content(colors))
        ft_error('c');
        
    splited = ft_split(colors, ',');
    if (!splited || sizeof_array(splited) != 3)
        ft_error('c');

    while (i < 3)
    {
        if (ft_strlen(splited[i]) > 3 && 
            (ft_strlen(splited[i]) - count_spaces(splited[i]) > 3))
            ft_error('c');
            
        color_array[i] = ft_atoi(splited[i]);
        if (color_array[i] < 0 || color_array[i] > 255)
            ft_error('c');
        i++;
    }
}

void set_colors(t_data *data, char *line)
{
    char *colors;
    int *color_array;

    color_array = select_color_array(data, line);
    if (!color_array)
        return;

    colors = extract_content(line + 1);
    parse_color_values(color_array, colors);
}

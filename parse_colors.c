#include "cub.h"

void set_colors(t_data *data, char *line)
{
	char *colors;
    char **splited;
    int *color_array;
	int i;

	i = 0;
    while (*line == ' ' || *line == '\t')
        line++;
    if (ft_strncmp(line, "F", 1) == 0)
        color_array = data->floor_color;
    else if (ft_strncmp(line, "C", 1) == 0)
        color_array = data->ceiling_color;
    else
        return;
    colors = extract_content(line + 1);
    splited = ft_split(colors, ',');
    if (!splited || sizeof_array(splited) != 3)
        ft_error('c');
	while (i < 3)
    {
        color_array[i] = atoi(splited[i]);
        if (color_array[i] < 0 || color_array[i] > 255)
        	ft_error('c');
		i++;
    }
}
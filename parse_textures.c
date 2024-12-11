#include "cub.h"

void set_texture(t_data *data, char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;

    if (ft_strncmp(line, "NO", 2) == 0)
        data->NO = extract_content(line + 2);
    else if (ft_strncmp(line, "SO", 2) == 0)
        data->SO = extract_content(line + 2);
    else if (ft_strncmp(line, "EA", 2) == 0)
        data->EA = extract_content(line + 2);
    else if (ft_strncmp(line, "WE", 2) == 0)
        data->WE = extract_content(line + 2);

}
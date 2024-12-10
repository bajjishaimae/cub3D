#include "cub.h"

int	open_cub_file(char *str)
{
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nError opening the file\n", 2);
		exit (1);
	}
	return (fd);
}
char *extract_content(char *line)
{
	int end;
    int start;
    char *content;
    end = ft_strlen(line) - 1;
    while (end >= 0 && (line[end] == ' ' || line[end] == '\t' || line[end] == '\n'))
        end--;
    start = 0;
    while (line[start] && (line[start] == ' ' || line[start] == '\t'))
        start++;
    content = malloc(sizeof(char) * (end - start + 2));
    if (!content)
        return (NULL);
    ft_strncpy(content, &line[start], end - start + 1);
    content[end - start + 1] = '\0';
    return (content);
}
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
    {
        ft_putstr_fd("Error\nInvalid color format\n", 2);
        exit(1);
    }
	while (i < 3)
    {
        color_array[i] = atoi(splited[i]);
        if (color_array[i] < 0 || color_array[i] > 255)
        {
            ft_putstr_fd("Error\nColor values must be in [0, 255]\n", 2);
            exit(1);
        }
		i++;
    }
}

void manip_line(t_data *data, char *line, int *nb, char **joined)
{
	if (strstr(line, "NO") || strstr(line, "EA") || strstr(line, "WE") || strstr(line, "SO"))
	{
		set_texture(data, line);
		(*nb)++;
	}
	else if (ft_strchr(line, 'F') || ft_strchr(line, 'C'))
	{
		set_colors(data, line);
		(*nb)++;
	}
	else
		*joined = ft_strjoin(*joined, line);

}
void manip_file(t_data *file_data, int fd)
{
	int valid_infonumber;
	char *line;
	char *joined;

	joined = ft_strdup("");
	valid_infonumber = 0;
	while (1)
	{

		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!ft_strcmp(line, "\n") || isonly_spaces(line))
			continue ;
		
		manip_line(file_data, line, &valid_infonumber, &joined);
	}
	file_data->map = ft_split(joined, '\n');
	if (file_data->map[0])
		valid_infonumber++;
	if (valid_infonumber != 7)
	{
		ft_putstr_fd("Error\n missing information\n", 2);
		exit(1);
	}
}

void parse(t_data *file_data, char *file_name)
{
	int	fd;

	fd = open_cub_file(file_name);
	manip_file(file_data, fd);
}
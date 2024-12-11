#include "cub.h"

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
        ft_error('a');
    ft_strncpy(content, &line[start], end - start + 1);
    content[end - start + 1] = '\0';
    return (content);
}


int manip_line(t_data *data, char *line, int *nb, char **joined)
{
	if (!ft_strncmp(line + skip_beg_spaces(line), "NO ", 3)
		|| !ft_strncmp(line + skip_beg_spaces(line), "SO ", 3)
		|| !ft_strncmp(line + skip_beg_spaces(line), "EA ", 3)
		|| !ft_strncmp(line + skip_beg_spaces(line), "WE ", 3))
	{
		set_texture(data, line);
		(*nb)++;
		return (1);
	}
	else if (!ft_strncmp(line + skip_beg_spaces(line), "F ", 2)
			|| !ft_strncmp(line + skip_beg_spaces(line), "C ", 2))
	{
		set_colors(data, line);
		(*nb)++;
		return (1);
	}
	else if (!ft_strncmp(line + skip_beg_spaces(line), "1", 1)
			|| !ft_strncmp(line + skip_beg_spaces(line), "0", 1))
	{
		*joined = ft_strjoin(*joined, line);
		return (1);
	}
	else 
		return (0);

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
		
		if (!manip_line(file_data, line, &valid_infonumber, &joined))
			ft_error('f');
	}
	file_data->map = ft_split(joined, '\n');
	if (file_data->map[0])
		valid_infonumber++;
	if (valid_infonumber != 7)
	{
		ft_error('f');
	}
}

void parse(t_data *file_data, char *file_name)
{
	int	fd;

	fd = open_cub_file(file_name);
	manip_file(file_data, fd);
	if (!surrounded_by_walls(file_data->map) || !space_btw_walls(file_data->map))
		ft_error('m');
	if (!composition_checker(file_data, 0, 0))
		ft_error('m');
	
}
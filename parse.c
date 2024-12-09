#include "cub.h"

int	open_cub_file(char *str, t_data *data)
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

void manip_file(t_data *file_data, int fd)
{
	int valid_infonumber;
	char *line;

	valid_infonumber = 0;
	while (1)
	{

		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "\n") || isonly_spaces(line))
			continue ;
		manip_line(file_data, line, &valid_infonumber);
	}
	if (valid_infonumber != 7)
	{
		ft_putstr_fd("Error\n missing information\n");
		exit(1);
	}
}

void parse(t_data *file_data, char *file_name)
{
	int	fd;

	fd = open_cub_file(file_name, file_data);
	manip_file(file_data, fd);
}
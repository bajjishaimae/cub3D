#include "cub.h"

int check_file_ext(char *str)
{
	while (*str)
	{
		if (*str == '.' && ft_strcmp(str, ".cub") == 0)
			return ;
		str++;
	}
	ft_putstr_fd("Error\nInvalid .cub extension\n", 2);
	exit(1);
}

int	main(int ac, char **av)
{

	t_data file_data;
	if (ac != 2)
	{
		printf("Error\nyou need 1 file , .cub file\n");
		return (1);
	}
	check_file_ext(av[1]);
	parse(&file_data, av[1]);
}
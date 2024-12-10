#include "cub.h"

void check_file_ext(char *str)
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
	printf("no path: %s\n", file_data.NO);
	printf("so path: %s\n", file_data.SO);
	printf("ea path: %s\n", file_data.EA);
	printf("we path: %s\n", file_data.WE);
	for(int i = 0; i < 3; i++)
	{
		printf("floor[%d] : %d\n", i, file_data.floor_color[i]);
	}
	for(int i = 0; i < 3; i++)
	{
		printf("ceiling[%d] : %d\n", i, file_data.ceiling_color[i]);
	}
	printf("this is map: \n");
	for (int i = 0; file_data.map[i]; i++)
	{
		printf("%s\n", file_data.map[i]);
	}
}
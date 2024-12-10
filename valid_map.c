#include "cub.h"

int surrounded_by_walls(char **map)
{
    int i;

    i = 0;
    while(map[0][i])
    {
        if (map[0][i] != '1')
            return (0);
        i++;
    }
	i = 0;
	while(map[sizeof_array(map) - 1][i])
    {
        if (map[sizeof_array(map) - 1][i] != '1')
            return (0);
        i++;
    }
	i = 0;
	while(map[i])
	{
		if (map[i][1] != '1' || map[ft_strlen(map[i]) - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
int space_btw_walls(char **map)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == ' ')
			{
				if ()
			}

		}


	}
}

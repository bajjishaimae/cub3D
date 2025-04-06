#include "cub.h"
int skip_beg_spaces(char *row)
{
	int i = 0;
	while(row[i] && row[i] == ' ')
		i++;
	return (i);
}
int skip_end_spaces(char *row)
{
	int i = ft_strlen(row) - 1;
	while(i && row[i] == ' ')
		i--;
	return (i);
}
int surrounded_by_walls(char **map, int i, int j, int k)
{
    i = skip_beg_spaces(map[0]);
    while(map[0][i])
    {
        if (map[0][i] != '1' && map[0][i] != ' ' && map[0][i] != '\n')
            return (0);
        i++;
    }
	i = skip_beg_spaces(map[sizeof_array(map) - 1]);
	while(map[sizeof_array(map) - 1][i])
    {
        if (map[sizeof_array(map) - 1][i] != '1' && map[sizeof_array(map) - 1][i] 
			!= ' ' && map[sizeof_array(map) - 1][i] != '\n')
            return (0);
        i++;
    }
	i = 0;
	while(map[i])
	{
		j = skip_beg_spaces(map[i]);
		k = skip_end_spaces(map[i]);
		if (map[i][j] != '1' || map[i][k] != '1')
			return (0);
		i++;
	}
	return (1);
}


static int is_valid_map_char(char c)
{
    return (c == '0' || c == 'N' || c == 'S' || 
            c == 'E' || c == 'W' || c == 'D');
}

static int check_previous_line(int i, char **map, int curr_len)
{
    int prev_len = (i == 0) ? 0 : ft_strlen(map[i - 1]);
    
    if (prev_len > curr_len)
    {
        while (curr_len < prev_len)
        {
            if (is_valid_map_char(map[i - 1][curr_len]))
                return 0;
            curr_len++;
        }
    }
    return 1;
}

static int check_next_line(int i, char **map, int curr_len)
{
    int next_len = (!map[i + 1]) ? 0 : ft_strlen(map[i + 1]);
    
    if (next_len > curr_len)
    {
        while (curr_len < next_len)
        {
            if (is_valid_map_char(map[i + 1][curr_len]))
                return 0;
            curr_len++;
        }
    }
    return 1;
}

int out_bounds(int i, char **map)
{
    int curr_len = ft_strlen(map[i]);
    
    if (!check_previous_line(i, map, curr_len))
        return 0;
    if (!check_next_line(i, map, curr_len))
        return 0;
    return 1;
}

int deep_surr_walls(char **map, int i, int j)
{
	while (map[i])
	{
		j = 0;
		if (!out_bounds(i, map))
		{
			return 0;
		}
		while (map[i][j])
		{
			if (i != 0 && j != 0 && j < ft_strlen(map[i]) && map[i+1])
			{
				if (map[i][j] == '0' || map[i][j] == 'E' || map[i][j] == 'N'
					|| map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'D')
				{
					if (is_space(map[i][j - 1]) || is_space(map[i][j + 1])
						|| is_space(map[i -1 ][j]) || is_space(map[i + 1][j]))
						return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int is_valid_map_char(char c)
{
    return (c == '1' || c == '0' || c == ' ' || 
            c == 'N' || c == 'S' || c == 'E' || 
            c == 'W' || c == 'D' || c == 'A' || 
            c == '\n');
}

static int process_map_char(t_data *data, int i, int j, int *p_counter)
{
    char current = data->map[i][j];

    if (!is_valid_map_char(current))
        return 0;

    if (current == 'N' || current == 'S' || 
        current == 'E' || current == 'W')
    {
        (*p_counter)++;
        data->x_player = j;
        data->y_player = i;
        data->direction = current;
    }
    else if (current == 'D')
        data->n_of_doors++;
    else if (current == 'A')
        data->sprite_n++;

    return 1;
}

int composition_checker(t_data *data, int i, int j)
{
    int p_counter = 0;
    data->n_of_doors = 0;
    data->sprite_n = 0;

    while (data->map[i])
    {
        while (data->map[i][j])
        {
            if (!process_map_char(data, i, j, &p_counter))
                return 0;
            j++;
        }
        j = 0;
        i++;
    }

    if (p_counter != 1)
        return 0;
    return 1;
}

void where_doors(t_data *data)
{
	int i = 0;
	int j ;
	int track = 0;
	data->doors = c_malloc(sizeof(t_door) * data->n_of_doors, 1);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'D')
			{
				data->doors[track].x = j;
				data->doors[track].y = i;
				track++;
			}
			j++;
		}
		i++;
	}
}

void where_sprites(t_data *data)
{
	int i = 0;
	int j ;
	int track = 0;

	data->sprites = c_malloc(data->sprite_n * sizeof(t_sprite), 1);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'A')
			{
				data->sprites[track].sprite_x = j;
				data->sprites[track].sprite_y = i;
				track++;
			}
			j++;
		}
		i++;
	}
}

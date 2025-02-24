#ifndef CUB_H
# define CUB_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
// #include "minilibx-linux/mlx.h"
# include <mlx.h>
# include <math.h>
# include <stdbool.h>
# include  <sys/time.h>
# define BUFFER_SIZE 10
# define pi M_PI
# define inf INFINITY
# define CELL_SIZE 16

typedef struct s_player
{
    double  x_pos;
    double  y_pos;
    double  x_dir;
    double  y_dir;
    double  plane_x;
    double  plane_y;
    double  fov;
}   t_player;

typedef struct s_ray
{
    double  rayd_x;
    double  rayd_y;
    double  delta_x;
    double  delta_y;
    double  side_x;
    double  side_y;
    int     step_x;
    int     step_y;
    // bool    hit_wall;
    // int     side_wall; // 0 : x_side , 1 : y_side
}   t_ray;

typedef struct s_image
{
    void        *img;
    int         bits_per_pixel;
    int         size_line;
    int         endian;
    char        *buffer;
}   t_img;

typedef struct s_line
{
    int line_order;
    int NO_line;
    int SO_line;
    int WE_line;
    int EA_line;
    int F_line;
    int C_line;
    int map_line;
} t_line;

typedef struct s_text
{
    void *img;
    char *addr;
    int width;
    int height;
    int endian;
    int bpp;
    int line_len;
} t_text;

typedef struct s_data
{
    t_player   player;
    void        *mlx_ptr;
    void        *mlx_win;
    int         screen_width;
    int         screen_height;
    double      fov;
    t_ray       ray;
    double      pwd;
    int         pixel_x;
    int         pixel_y;
    t_img       img;
    char **map;
    t_line order;
    char *NO;
    char *WE;
    char *EA;
    char *SO;
    int floor_color[3];
    int ceiling_color[3];
    int map_width;
    int map_lenght;
    int x_player;
    int y_player;
    char direction;
    int end_map;
    t_text north;
    t_text south;
    t_text east;
    t_text west;
    int side_wall;
    double wall_x;
} t_data;


typedef struct s_coll
{
	void			*ptr;
	struct s_coll	*next;
}	t_coll;

char	*ft_strchr(const char *string, int c );
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
int	ft_strlen(char *s);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *s);
int	ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
void parse(t_data *file_data, char *file_name);
int	isonly_spaces(char *input);
int sizeof_array(char **str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
int skip_beg_spaces(char *row);
int skip_end_spaces(char *row);
void ft_error(char type);
void set_texture(t_data *data, char *line);
void set_colors(t_data *data, char *line);
int	open_cub_file(char *str);
int surrounded_by_walls(char **map);
int deep_surr_walls(char **map);
int	composition_checker(t_data *data, int i, int j);
char *extract_content(char *line);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
void	*c_malloc(size_t size, int flag);
void map_lenght(t_data *data);
void map_width(t_data *data);
int	is_space(char c);
int count_spaces(char *number);
void load_all_text(t_data *data);
void destroy_text(t_data *data);
void check_file_ext(char *str);
int convert_rgb(int r, int g, int b);
t_text get_wall_texture(t_data *data, int side, double rayd_x, double rayd_y);
//
void	init_data(t_data *data);
void	init_player(t_data *data);
void    raycast(t_data *data);
void    init_dist(t_data *data, int x);
int     move(int key_code, t_data *data);
void    put_pixel_to_image(t_data *data, int x, int y, int color);
int     render_minimap(t_data *data);
int     render_frame(t_data *data);
int     ft_destroy_win(t_data *data);
int     mouse_move(int x, int y, t_data *data);
#endif
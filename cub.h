#ifndef CUB_H
# define CUB_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
# include <limits.h>

# define BUFFER_SIZE 10

typedef struct s_data
{
    char **map;
    char *NO;
    char *WE;
    char *EA;
    char *SO;
    int floor_color[3];
    int ceiling_color[3];
    int map_width;
    int map_lenght;
} t_data;

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


#endif
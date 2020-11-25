/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 21:08:43 by aymaatou          #+#    #+#             */
/*   Updated: 2020/11/25 12:07:16 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

/*********
 * Library
 * ***/
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
///////////////////


/*************
 *  DEFINE
 * * */
/////////////////////COLORS////////////////
#define WHITE 0xFFFFFF
#define RED 0xFF0000
#define GREEN 0x008000
#define PURPLE 0x800080
#define YELLOW 0xFFFF00
#define GRAY 0x808080
#define BLACK 0x000000

//////////////////////////
#define BUFFER_SIZE 1024
#define TILE 32





/********
 * Structs
 * *****/

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

t_data  g_data;

typedef struct
{
    void *mlx_ptr;
    void *win_ptr;
} t_mlx;

t_mlx g_mymlx;

typedef struct
{
    int width_resolution;
    int height_resolution;
    char *no_t;
    char *so_t;
    char *we_t;
    char *ea_t;
    char *sprit;
    char *flor;
    char *cilng;
    char **map;
    int hight;
    int width;
    
} t_file;

t_file g_file;

/**************************************
 *              Functions
 * ****************************/
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
size_t	ft_strlen(const char *str);
char	*ft_strdup(char const *s1);
char	*ft_strjoin(char   *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	    get_next_line(int fd, char **line);
void ft_get_handle(char *g_value);
int	ft_isalnum(int str);
int	ft_isalpha(int c);
int	ft_isdigit(int str);
char		*ft_strtrim(char const *s1, char const *set);
int		ft_atoi(const char *str);
char		**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_bzero(void *b, size_t len);

/***********
 * file handele
 * ****/
void ft_map_handle(char *r_file, int map_size);
void ft_openfile(char *r_file);
void ft_get_handle(char *g_value);
void ft_get_sprit(char *value);
void ft_get_texture(char c, char *value);
void ft_get_resolution(int v, int h);


/*********
 * Draw Functions
 * ********/
void ft_map();

#endif
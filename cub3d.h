/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 21:08:43 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/08 18:31:52 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

/*********
 * Libs
 * *********/
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
///////////////////

/******************
 *  DEFINED VALUES
 ******************/

/////////////////////COLORS////////////////
#define WHITE 0xFFFFFF
#define RED 0xFF0000
#define GREEN 0x008000
#define PURPLE 0x800080
#define YELLOW 0xFFFF00
#define GRAY 0x808080
#define BLACK 0x000000

//////////////Bouton////////////
#define UP 126
#define UP_l 13
#define DOWN 125
#define DOWN_l 1
#define RIGHT 123
#define RIGHT_l 0
#define LEFT 124
#define LEFT_l 2

//////////////////////////
#define BUFFER_SIZE 1024
#define TILE 64

/**************
 * Structs
 * **********/
typedef struct
{
    int isRayFacingDown;
    int isRayFacingUp;
    int isRayFacingRight;
    int isRayFacingLeft;

} t_cast;

t_cast g_cast;

typedef struct
{
    double HorizWallHitX;
    double HorizWallHitY;
    int HorizWallHit;
    double VertWallHitX;
    double VertWallHitY;
    int VertWallHit;

} t_wallhits;

t_wallhits g_wallhits;

typedef struct
{
    float ray_angle;
    float wallHitx;
    float wallHity;
    float distance;
    int wasVerticale;
    int rayfacingUP;
    int rayfacingDown;
    int rayfacingRight;
    int rayfacingLeft;
    int wallhitcont;
    int top;
    int bottom;
    float wallheight;

} t_ray;

t_ray g_ray[3200];

typedef struct s_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

t_data g_data;

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
    int flor;
    int cilng;
    char **map;
    int hight;
    int width;
    int counter;

} t_file;

t_file g_file;

typedef struct
{
    float x;
    float y;
    float radius;
    int turnDirection;
    int walkDirection;
    int sidewalk;
    float rotationAngle;
    float move_speed;
    float rotation_speed;
    int ishere;
} t_player;

t_player g_myplayer;

typedef struct 
{
    void *img;
    int *data;
    int img_width;
    int img_height;  
    
} t_txt;

t_txt g_txt[5];
/**************************************
 *              Functions
 * ****************************/

void my_mlx_pixel_put(t_data *data, int x, int y, int color);
size_t ft_strlen(const char *str);
char *ft_strdup(char const *s1);
char *ft_strjoin(char *s1, char *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);
int get_next_line(int fd, char **line);
void ft_get_handle(char *g_value);
int ft_isalnum(int str);
int ft_isalpha(int c);
int ft_isdigit(int str);
char *ft_strtrim(char const *s1, char const *set);
int ft_atoi(const char *str);
char **ft_split(char const *s, char c);
void *ft_calloc(size_t count, size_t size);
void *ft_bzero(void *b, size_t len);
void	ft_putstr(char *s);
int	ft_memcmp(const void *s1, const void *s2, size_t n);


/***********
 * file handele
 * *********/

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
void draw_line(int x0, int y0, int x1, int y1, int color);
int iswall(float x, float y);
void cast_rays(void);
void ft_rayCaster(int i, double rayAngle);
double d2r(double angle);
void ft_drw_player(void);
void get_data_textures ();

/***********************
 *  RayCating Functions
 * ********************/

void ft_ray(int i, double rayAngle);
void ft_horizntale_inter(double rayAngle);
void ft_verticale_inter(double rayAngle);
void ft_get_distance(double rayAngle, int i);
double ft_distance_between(double x1, double y1, double x2, double y2);

/****************************
 *  Error handling Functions
 ***************************/

void    ft_map_arg_check(char *arg);
void    ft_save_arg_check(char *arg);
int     ft_xmp_check(char *arg);
void    ft_map_error_check();
void 	*ft_error(char *str);

/***********************
*   Screenshot function
****************/
void creat_screenshot(void);



/****************************
        Sprite
*********************************/
void    ft_get_sp_pos(float x, float y, int i);
int     g_sp_index;
typedef struct {
    float x;
    float y;
    float dis;
    float y_off;
    float x_off;
    float size;
}t_sprite_info;

t_sprite_info g_sprite[3200];
void	sort(void);
void	draw_sprite(int id);
void	ft_sp_data (int i);
#endif
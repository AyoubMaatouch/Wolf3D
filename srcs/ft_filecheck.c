/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filecheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:49:26 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/04 10:24:01 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_get_resolution(int hight, int width)
{
    g_file.height_resolution = hight;
    g_file.width_resolution = width;
    g_file.counter++;
}

void ft_get_texture(char c, char *value)
{
    if (c == 'N'){
         if (!(ft_xmp_check(value)))
            {
            perror("Error\nPlease Check 'NO' texture File\n");
            exit(0);
            }
        else
        g_file.no_t = value;
        }
    else if (c == 'W'){
         if (!ft_xmp_check(value))
            {
            perror("Error\nPlease Check 'WE' texture File\n");
            exit(0);
            }
        else
        g_file.we_t = value;
        }
    else if (c == 'E'){
         if (!ft_xmp_check(value) )
            {
            perror("Error\nPlease Check 'EA' texture File\n");
            exit(0);
            }
        else
        g_file.ea_t = value;
        }
    else{
        if (!ft_xmp_check(value))
            {
            perror("Error\nPlease Check 'SO' texture File\n");
            exit(0);
            }
        else
         g_file.so_t = value;
        }
}

void ft_get_sprit(char *value)
{
    if (!ft_xmp_check(value))
            {
            perror("Error\nPlease Check 'Sprite' XPM File\n");
            exit(0);
            }
    g_file.sprit = value;
}

void ft_get_cf(char c, char *value)
{
    if (c == 'F')
    {
        char **temp = ft_split(value , ',');
        g_file.flor = 65536 * ft_atoi(temp[0]) + 256 *ft_atoi(temp[1]) + ft_atoi(temp[2]);;
        }
    else
       {
        char **temp = ft_split(value , ',');
        g_file.cilng = 65536 * ft_atoi(temp[0]) + 256 *ft_atoi(temp[1]) + ft_atoi(temp[2]);;; 
       }
}

void ft_get_handle(char *g_value)
{
    char **temp;

    temp = ft_split(g_value, ' ');
    if (g_value[0] == 'R')
        ft_get_resolution(ft_atoi(temp[2]), ft_atoi(temp[1]));
    if (g_value[0] == 'W' || g_value[0] == 'N' || (g_value[0] == 'S' && g_value[1] == 'O') || g_value[0] == 'E')
        ft_get_texture(g_value[0], temp[1]);
    if (g_value[0] == 'F' || g_value[0] == 'C')
        ft_get_cf(g_value[0], temp[1]);
    if (g_value[0] == 'S' && g_value[1] != 'O')
        ft_get_sprit(temp[1]);
    free(temp);
}

void ft_map_handle(char *r_file, int map_size)
{
    int fd = open(r_file, O_RDONLY);
    char *line;
    int i = 0;
    g_file.hight = map_size;
    g_file.map = malloc(sizeof(char *) * (map_size + 1));
    g_file.map[map_size] = NULL;
    while ((get_next_line(fd, &line)))
    { 
        if (!g_file.width || g_file.width < (int)ft_strlen(line))
            g_file.width = (int)ft_strlen(line);
        
        if (ft_isdigit(ft_strtrim(line, " ")[0]))
        {
            g_file.map[i] = ft_strdup(line);
            i++;
        }
        free(line);
    }
    if (ft_isdigit(ft_strtrim(line, " ")[0]))
        g_file.map[i] = ft_strdup(line);
    free(line);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 09:58:21 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/08 18:57:24 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <string.h>

void    ft_map_arg_check(char *arg)
{
    if (ft_memcmp(&arg[strlen(arg) - 4], ".cub", 5) != 0)
            ft_error("Error\nWrong File Name!\nTry Again :)\n");
}

void    ft_save_arg_check(char *arg)
{
    if (ft_memcmp(arg, "--save", 5) != 0)
            ft_error("Error\nWrong Argument Name!\nTry : --save :)\n");
} 

int ft_xmp_check(char *arg)
{
       if (ft_memcmp(&arg[strlen(arg) - 4], ".xpm", 5) != 0)
      { 
           return (0);
      }
      return (1);
}

void  ft_first_last_line(void)
{
      int i = 0;
      int j;
      while (i < g_file.hight)
      {
            j = 0;
            while (j < (int)ft_strlen(g_file.map[g_file.hight - 1]))
            {
                  if (i > 0 && g_file.map[i][j] == '0' && g_file.map[i + 1][j] == ' ')
                        ft_error("Error\nCheck Your Map! 1\n");
                  if (g_file.map[0][j] != '1' && g_file.map[0][j] != ' ')
                             ft_error("Error\nCheck your Map! 2\n");
                       if (g_file.map[i][j] == ' ' && (g_file.map[i][j + 1] == '0' || g_file.map[i][j + 1] == '2'))
                             ft_error ("Error\nCheck Your Map! 3\n");
                       if   ( i > 0 && (g_file.map[i + 1]) != NULL  && g_file.map[i][j] == ' ' 
                               && (g_file.map[i + 1][j] == '0' || g_file.map[i][j + 1] == '2'))
                               ft_error ("Error\nCheck Your Map! 4\n");
                        if (j == (g_file.hight - 1 ) && g_file.map[g_file.hight - 1][j] != '1' 
                              && g_file.map[g_file.hight - 1][j] != ' ')
                             ft_error("Error\nCheck your Map 5\n");
                        j++;
            }                      
            i++;
      }
}


void ft_map_error_check()
{
      ft_first_last_line();
      
      int i;

      i  = 1;
   
}

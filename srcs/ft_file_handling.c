/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 09:58:21 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/07 20:18:05 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <string.h>

void    ft_map_arg_check(char *arg)
{
    if (strcmp(&arg[strlen(arg) - 4], ".cub") != 0)
      { 
            perror("ERROR\nWrong File Name!\nTry Again :)\n");
            exit (0);
      }
}
void    ft_save_arg_check(char *arg)
{
    if (strcmp(arg, "--save") != 0)
      { 
            perror("ERROR\nWrong Argument Name!\nTry : --save :)\n");
            exit (0);
      }
} 
int ft_xmp_check(char *arg)
{
       if (strcmp(&arg[strlen(arg) - 4], ".xpm") != 0)
      { 
           return (0);
      }
      return (1);
}


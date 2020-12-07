# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 18:00:47 by aymaatou          #+#    #+#              #
#    Updated: 2020/12/07 20:35:57 by aymaatou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

LIB = Lib/*.c
SRC = srcs/*.c
CC = gcc  -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -Wall -Wextra -Werror 

#CC = gcc -I /usr/X11/include -g -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit -Wall -Wextra -Werror


all : $(NAME)

$(NAME):
	@$(CC) cub3d.c $(LIB) $(SRC) -o cub3D
	
clean :
	@rm -fr $(NAME) cub3D.dSYM

fclean : clean
	@rm -fr $(NAME) cub3D.dSYM

re : fclean all

run : 
	@./$(NAME) *.cub

#.PHONY : all clean fclean re $(NAME)
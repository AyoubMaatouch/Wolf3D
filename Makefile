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
CC = gcc  -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit  -Wall -Wextra -Werror libmlx.dylib -fsanitize=address -g
#CC = gcc -I /usr/X11/include -g -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit -Wall -Wextra -Werror


all : $(NAME)

$(NAME):
	@make -C mlx_beta/.
	@echo "\nCompilation of MLX lib:	[\033[1;32mDONE\033[m]"
	@cp -r mlx_beta/libmlx.dylib .
	@$(CC) cub3d.c $(LIB) $(SRC) -o cub3D
	@echo "Compilation of $(NAME):	[\033[1;32mDONE\033[m]"
	
clean :
	@make clean -C mlx_beta/.
	@rm -fr $(NAME) cub3D.dSYM *.
	@echo "Deleting Files:	[\033[1;31mDONE\033[m]"

fclean : clean
	@rm -fr $(NAME) cub3D.dSYM first_rendered_image.bmp libmlx.dylib

re : fclean all

run : re
	@./$(NAME) *.cub

save : 
	@./$(NAME) *.cub --save
	@echo "Rendring image $(NAME):	[\033[1;32mDONE\033[m]"

.PHONY : all clean fclean re $(NAME)
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

LIB = Lib/{ft_atoi,ft_bzero,ft_calloc,ft_isalnum,ft_isalpha,ft_isdigit,ft_memcmp,ft_putstr,ft_split,ft_strdub_strjoin,ft_strlen,ft_strtrim}.c
SRC = srcs/{cub3d_raycasting,cub3d_tools,cub3d_tools_2,ft_draw,ft_file_handling,ft_filecheck,ft_filecheck_2,ft_game,ft_intersections,ft_mlx_loops,ft_screenshot,get_next_line}.c
CC = gcc  -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit  -Wall -Wextra -Werror  libmlx.dylib -fsanitize=address -g
REG = srcs/{cub3d_sprite,ft_3drendring}.c
BONUS = bonus/{cub3d_sprite_bonus,ft_3drendring_bonus}.c

all : $(NAME)

$(NAME):
	@make -C mlx_beta/.
	@echo "\nCompilation of MLX lib:	[\033[1;32mDONE\033[m]"
	@cp -r mlx_beta/libmlx.dylib .
	@$(CC) cub3d.c $(LIB) $(SRC) $(REG) -o cub3D
	@echo "Compilation of $(NAME):	[\033[1;32mDONE\033[m]"
	
clean :
	@make clean -C mlx_beta/.
	@rm -rf $(NAME) cub3D.dSYM *.
	@echo "Deleting Files:	[\033[1;31mDONE\033[m]"

fclean : clean
	@rm -rf $(NAME) cub3D.dSYM first_rendered_image.bmp libmlx.dylib

re : fclean all

run :
	@./$(NAME) maps/map3.cub

save : 
	@./$(NAME) *.cub --save
	@echo "Rendring image $(NAME):	[\033[1;32mDONE\033[m]"
bonus : fclean 
	@make -C mlx_beta/.
	@echo "\nCompilation of MLX lib:	[\033[1;32mDONE\033[m]"
	@cp -r mlx_beta/libmlx.dylib .
	@$(CC) cub3d.c $(LIB) $(SRC) $(BONUS) -o cub3D
	@echo "Compilation of $(NAME):	[\033[1;32mDONE\033[m][\033[1;36mBONUS\033[m]"

.PHONY : all clean fclean re $(NAME)
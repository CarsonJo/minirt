SRC =	main.c \
		hook.c\
		help_function/ft_bzero.c\
		help_function/make_cam_to_world.c\
		help_function/operation.c\
		help_function/operation2.c\
		help_function/base_operation.c\
		help_function/make_cylinder_mat.c\
		help_function/determinant.c\
		help_function/world_to_cam.c\
		help_function/operation3.c\
		color_pixel.c\
		draw.c\
		error.c\
		object_mov.c\
		handle_click.c\
		object/cylinder.c\
		object/cylinder2.c\
		object/sphere.c\
		object/plane.c\
		object/plane2.c\
		object/utils_object.c\
		bright_pixel.c\
		get_next_line_utils.c\
		get_next_line.c\
		ft_split.c\
		pars_utils.c\
		pars.c\
		pars2.c\
		pars3.c\
		pars4.c\
		pars5.c\
		pars6.c\
		pars7.c\
		norm.c\
		norm2.c\



OBJ = $(SRC:%.c=%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

INCLUDE = -Iminilibx-linux

LINK = -Lminilibx-linux  -lXext -lX11 -lmlx -g -lm

NAME = minirt

MINILIB = minilibx-linux

all : $(NAME)

$(NAME) : $(MINILIB) $(OBJ)
	cc $(OBJ) $(LINK) -o $(NAME)

$(MINILIB) :
	git clone git@github.com:42Paris/minilibx-linux.git
	make -C ./$(MINILIB)

%.o: %.c
	$(CC) -c $^ -o $@ $(INCLUDE) $(CFLAGS)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

to_push : fclean
	rm -rf $(MINILIB)

re : fclean
	make all

.PHONY : all clean fclean re
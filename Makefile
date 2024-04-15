SRC =	main.c \
		draw.c

OBJ = $(SRC:%.c=%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

INCLUDE = -Iminilibx-linux

LINK = -Lminilibx-linux  -lXext -lX11 -lmlx -g -lm

NAME = minirt

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(OBJ) $(LINK) -o $(NAME)

%.o: %.c
	$(CC) -c $^ -o $@ $(INCLUDE) $(CFLAGS)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean
	make all

.PHONY : all clean fclean re
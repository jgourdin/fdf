SRCS = 	main.c draw.c 

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

NAME = fdf

LIBS = libft/libft.a\

all: $(NAME)

$(NAME):
		make -C ./libft
		make -C ./minilibx_macos
		gcc $(FLAGS) -c $(SRCS)
		$(CC) $(FLAGS) $(OBJS) $(LIBS) -o $(NAME) -framework OpenGL -framework AppKit -I minilibx_macos ./minilibx_macos/libmlx.a

clean: clean
		rm -rf $(OBJS)
		make -C ./libft clean
		make -C ./minilibx_macos clean 
fclean: fclean
		rm -rf $(NAME)
		make -C ./libft fclean

re: fclean all

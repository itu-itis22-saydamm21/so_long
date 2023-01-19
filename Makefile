NAME = so_long

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iheaders/

SOURCE = $(wildcard game_logic/*.c) $(wildcard get_next_line/*.c)

OBJS = $(SOURCE:.c=.o)

RM = rm -rf

LFLAGS = -Lminilibx -lmlx -framework OpenGL -framework AppKit

MFLAGS = ./minilibx/libmlx.a

all :$(MFLAGS) $(NAME)

$(MFLAGS):
	make -C ./minilibx

$(NAME): $(OBJS)
	$(CC) $(LFLAGS) $(MFLAGS) $(CFLAGS) $(OBJS) -o $(NAME)

fclean : clean
	make -C ./minilibx
	$(RM) $(NAME)

clean :
	make -C ./minilibx
	$(RM) ./game_logic/*.o ./get_next_line/*.o ./minilibx/*.o

re: fclean all

.PHONY : all fclean clean re
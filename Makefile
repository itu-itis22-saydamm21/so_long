NAME := so_long

CC := gcc

CFLAGS := -Wall -Wextra -Werror -Iheaders/

SOURCE := $(wildcard game_logic/*.c) $(wildcard get_next_line/*.c)

OBJS := $(SOURCE:.c=.o)

LIBRARY := -Lminilibx -lmlx -framework OpenGL -framework AppKit
# LFLAGS
MINILIBX := minilibx/

all: $(NAME)

.c.o:
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(MINILIBX)
	$(CC) $(LIBRARY) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
		make clean -C $(MINILIBX)
		rm -rf $(NAME)

re: fclean all

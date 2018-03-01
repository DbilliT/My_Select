SRC	= src/main.c \
	  src/term_init.c \
	  src/list_init.c \
	  src/display_screen.c \
	  src/cursor_move.c \
	  src/main_loop.c \
	  src/echo_selection.c \
	  src/linked_action.c

NAME	= my_select

CFLAGS	= -I./include/ -W -Wall -Wextra -Werror

LIB	= -L./lib/ -lmy \
	  -L/usr/lib/ -lncurses

OBJ	= $(SRC:.c=.o)

CC	= gcc

RM	= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./lib/my
	make clean -C ./lib/my
	$(CC) $(OBJ) -o $(NAME) $(LIB)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

NAME		= wolf3d
SRCS		= main.c \
			  wolf3d.c \
			  game.c \
			  maps.c \
			  reader.c \
			  load.c \
			  graphic.c \
			  raytracer.c \
			  player.c \
			  audio.c
SRCSPATH	= ./srcs/
INCLUDES	= ./includes
CC			= clang
CFLAGS		= -Wall -Werror -Wextra -O2
SDL_CONFIG	= ~/.brew/Cellar/sdl2/2.0.4/bin/sdl2-config
INCLUDES_O	= -I $(INCLUDES) -I ./libft/includes
INCLUDES_C	= -L ~/.brew/Cellar/sdl2/2.0.4/lib -lSDL2 -lSDL2main `$(SDL_CONFIG) --cflags --libs` -L ./libft -lft
SRC			= $(addprefix $(SRCSPATH), $(SRCS))
OBJS		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C	./libft
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES_C) 

%.o: %.c
	$(CC) -o $@ $(INCLUDES_O) $(CFLAGS) -c $<

clean:
	make -C ./libft clean
	rm -rf $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re

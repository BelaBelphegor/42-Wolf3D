NAME		= pokemon-origins
SRCS		= main.c
SRCSPATH	= ./srcs/
INCLUDES	= ./includes/ 
CC			= clang
CFLAGS		= -Wall -Werror -Wextra -O2
SDL_CONFIG	= ~/.brew/Cellar/sdl2/2.0.4/bin/sdl2-config
INCLUDES_O	= -I $(INCLUDES) -I ~/.brew/Cellar/sdl2/2.0.4/include
INCLUDES_C	= -L ~/.brew/Cellar/sdl2/2.0.4/lib -lSDL2 -lSDL2main `$(SDL_CONFIG) --cflags --libs`
SRC			= $(addprefix $(SRCSPATH), $(SRCS))
OBJS		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES_C) 

%.o: %.c
	$(CC) -o $@ $(INCLUDES_O) $(CFLAGS) -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re

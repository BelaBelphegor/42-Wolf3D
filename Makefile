NAME				= wolf3d
SRCS				= main.c \
					  wolf3d.c \
			  		  game.c \
					  maps.c \
			  		  reader.c \
				 	  load.c \
			  		  graphic.c \
			 		  raytracer.c \
		  			  player.c \
					  audio.c \
					  inputs.c
SRCSPATH			= ./srcs/
INCLUDES			= ./includes
CC					= clang
CFLAGS				= -Wall -Werror -Wextra -O0 -g
LFLAGS				= -L ./libft/ -lft
SDL2				= -framework SDL2
SDL2_MIXER			= -framework SDL2_mixer
SDL2_HEADER 		= -I ~/Library/Frameworks/SDL2.framework/Headers
SDL2_HEADER_MIXER	= -I ~/Library/Frameworks/SDL2_mixer.framework/Headers
SDL					= -F ~/Library/Frameworks $(SDL2_MIXER) $(SDL2)
SDL_HEADER			= -F ~/Library/Frameworks $(SDL2_HEADER_MIXER) $(SDL2_HEADER)
INCLUDES_O			= -I $(INCLUDES) -I ./libft/includes
INCLUDES_C			= $(SDL) $(SDL_HEADER) $(LFLAGS)
SRC					= $(addprefix $(SRCSPATH), $(SRCS))
OBJS				= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C	./libft
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES_C) 

%.o: %.c
	$(CC) -o $@ $(INCLUDES_O) $(CFLAGS) $(SDL_HEADER) -c $<

clean:
	make -C ./libft clean
	rm -rf $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all

sdl_install:
	curl https://dl.dropboxusercontent.com/u/22561204/SDL/Archive.zip > /tmp/Archive.zip
	unzip -o /tmp/Archive.zip -d ~/Library/Frameworks/

.PHONY: all clean fclean re

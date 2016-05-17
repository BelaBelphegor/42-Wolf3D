/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 15:46:49 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/17 17:20:22 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WOLF3D_H
# define FT_WOLF3D_H

#include <SDL2/SDL.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
# define DESIRED_FRAME 60
# define WINDW_W 1280
# define WINDW_H 966
# define SCREEN_FPS 60
# define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS

typedef struct 		s_wolf_m3d
{
	char			**map;
}					t_wmap;			

typedef struct		s_wolf3d
{
	SDL_Window		*pWindow;
	SDL_Renderer	*renderer;
	// Frames per s timer
	int				frame;
	t_wmap			*map;
}					t_wolf3d;

int					readfile(char *file, char *buffer);
t_wolf3d			*wolf3d_create(void);
t_wmap				*woldf3d_map_create(void);
int					wolf3d_loader(t_wolf3d *wolf);
void				wolf3d_core(t_wolf3d *wolf);
int					wolf3d_init_map(t_wmap *map, char *buffer);
void				wolf3d_map_destroy(t_wmap *map);
int					wolf3d_init_graphics(t_wolf3d *wolf);
void				wolf3d_close(t_wolf3d *wolf);
void				wolf3d_destroy_graphics(t_wolf3d *wolf);
#endif

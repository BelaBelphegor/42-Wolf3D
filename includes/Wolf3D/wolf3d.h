/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 15:46:49 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/06 21:15:20 by tiboitel         ###   ########.fr       */
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
#include <math.h>
# define DESIRED_FRAME 60
# define WINDW_W 1680 
# define WINDW_H 1080
# define SCREEN_FPS 60
# define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS
# define MOVE_SPEED_MODIFIER 5.0
# define ROT_SPEED_MODIFIER 3.0

typedef struct		s_wolf_raycaster
{
	double			planex;
	double			planey;
	double			camerax;
	double			rayposx;
	double			rayposy;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	// render
	int				lineheight;
	int				drawstart;
	int				drawend;
}					t_wraycaster;

typedef struct		s_wolf_player
{
	double			x;
	double			y;
	double			dirx;
	double			diry;
	double			movespeed;
	double			rotspeed;
}					t_wplayer;

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
	t_wplayer		player;
	t_wraycaster	raycaster;
	SDL_Texture		*texture;
	double			frametime;
}					t_wolf3d;

int					readfile(char *file, char *buffer);
t_wolf3d			*wolf3d_create(void);
t_wmap				*wolf3d_map_create(void);
int					wolf3d_loader(t_wolf3d *wolf);
void				wolf3d_core(t_wolf3d *wolf);
int					wolf3d_init_map(t_wmap *map, char *buffer);
void				wolf3d_map_destroy(t_wmap *map);
int					wolf3d_init_graphics(t_wolf3d *wolf);
void				wolf3d_close(t_wolf3d *wolf);
void				wolf3d_destroy_graphics(t_wolf3d *wolf);
void				wolf3d_raycaster(t_wolf3d *wolf);
void				wolf3d_draw_raycaster(t_wolf3d *wolf, unsigned int x);
void				wolf3d_raycaster_sidestep(t_wolf3d *wolf);
void				wolf3d_raycaster_rayhit(t_wolf3d *wolf);
void				wolf3d_render(t_wolf3d *wolf);
void				wolf3d_update(t_wolf3d *wolf);
double				wolf3d_player_get_movespeed(t_wolf3d *wolf);
double				wolf3d_player_get_rotspeed(t_wolf3d *wolf);
void				wolf3d_inputs(const unsigned char *keystate, t_wolf3d *wolf);
#endif

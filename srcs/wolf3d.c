/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:04:46 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/17 19:47:34 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

t_wolf3d	*wolf3d_create(void)
{
	t_wolf3d	*wolf;

	wolf = NULL;
	if (!(wolf = (t_wolf3d *)ft_memalloc(sizeof(t_wolf3d))))
		return (NULL);
	wolf->pWindow = NULL;
	wolf->renderer = NULL;
	wolf->frame = 0;
	wolf->map = NULL;
	wolf->map = wolf3d_map_create();
	return (wolf);
}

void		wolf3d_core(t_wolf3d *wolf)
{
	SDL_Event			e;
	Uint8				*keystate;

	wolf->player.x = 3;
	wolf->player.y = 3;
	wolf->player.dirx = -1;
	wolf->player.diry = -1;
	wolf->raycaster.planex = -0.33;
	wolf->raycaster.planey = 0.66;
	wolf->frametime = 0;
	wolf->quit = 1;
	keystate = NULL;
	keystate = (Uint8 *)SDL_GetKeyboardState(NULL);
	if (!keystate)
		return ;

	while (wolf->quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				wolf->quit = 0;
		}
		wolf3d_inputs(keystate, wolf);
		wolf3d_update(wolf);
	}
}

void		wolf3d_inputs(const unsigned char *keystate, t_wolf3d *wolf)
{
	int		x;
	int		y;
	double	olddirx;
	double	oldplanex;

	x = 0;
	y = 0;
	if (keystate[SDL_SCANCODE_ESCAPE])
		wolf->quit = 0;
	if (keystate[SDL_SCANCODE_UP])
	{
			x = (int)(wolf->player.x + wolf->player.dirx
					* wolf3d_player_get_movespeed(wolf));
			y = (int)(wolf->player.y);
			if (x && y && wolf->map->map[x][y] && wolf->map->map[x][y] == '0')
				wolf->player.x += wolf->player.dirx * wolf3d_player_get_movespeed(wolf);
			x = (int)(wolf->player.x);	
			y = (int)(wolf->player.y + wolf->player.diry
					* wolf3d_player_get_movespeed(wolf));
			if (x && y && wolf->map->map[x][y] == '0')
				wolf->player.y += wolf->player.diry * wolf3d_player_get_movespeed(wolf);	
	}
	if (keystate[SDL_SCANCODE_DOWN])
	{
			x = (int)(wolf->player.x - wolf->player.dirx
					* wolf3d_player_get_movespeed(wolf));
			y = (int)(wolf->player.y);
			if (x && y && wolf->map->map[x][y] && wolf->map->map[x][y] == '0')
				wolf->player.x -= wolf->player.dirx * wolf3d_player_get_movespeed(wolf);
			x = (int)(wolf->player.x);	
			y = (int)(wolf->player.y - wolf->player.diry
					* wolf3d_player_get_movespeed(wolf));
			if (x && y && wolf->map->map[x][y] == '0')
				wolf->player.y -= wolf->player.diry * wolf3d_player_get_movespeed(wolf);	
	}
	if (keystate[SDL_SCANCODE_RIGHT])
	{
		olddirx = wolf->player.dirx;
		oldplanex = wolf->raycaster.planex;
		wolf->player.dirx = wolf->player.dirx * cos(-wolf3d_player_get_rotspeed(wolf)) -
			wolf->player.diry * sin(-wolf3d_player_get_rotspeed(wolf));
		wolf->player.diry = olddirx * sin(-wolf3d_player_get_rotspeed(wolf)) +
			wolf->player.diry * cos(-wolf3d_player_get_rotspeed(wolf));
		wolf->raycaster.planex = wolf->raycaster.planex * cos(-wolf3d_player_get_rotspeed(wolf)) -
			wolf->raycaster.planey * sin(-wolf3d_player_get_rotspeed(wolf));
		wolf->raycaster.planey = oldplanex * sin(-wolf3d_player_get_rotspeed(wolf)) +
			wolf->raycaster.planey * cos(-wolf3d_player_get_rotspeed(wolf));
	}
	if (keystate[SDL_SCANCODE_LEFT])
	{
		olddirx = wolf->player.dirx;
		oldplanex = wolf->raycaster.planex;
		wolf->player.dirx = wolf->player.dirx * cos(wolf3d_player_get_rotspeed(wolf)) -
			wolf->player.diry * sin(wolf3d_player_get_rotspeed(wolf));
		wolf->player.diry = olddirx * sin(wolf3d_player_get_rotspeed(wolf)) +
			wolf->player.diry * cos(wolf3d_player_get_rotspeed(wolf));
		wolf->raycaster.planex = wolf->raycaster.planex * cos(wolf3d_player_get_rotspeed(wolf)) -
			wolf->raycaster.planey * sin(wolf3d_player_get_rotspeed(wolf));
		wolf->raycaster.planey = oldplanex * sin(wolf3d_player_get_rotspeed(wolf)) +
			wolf->raycaster.planey * cos(wolf3d_player_get_rotspeed(wolf));
	}
}

void		wolf3d_update(t_wolf3d *wolf)
{
	unsigned int	execution_time;
	unsigned int	remaining_time;
	unsigned int	current_time;

	current_time = SDL_GetTicks();
	wolf3d_raycaster(wolf);
	wolf3d_render(wolf);
	execution_time = SDL_GetTicks() - current_time;
	remaining_time = ((int)(SCREEN_TICKS_PER_FRAME - execution_time)
			< 0) ? 0 : SCREEN_TICKS_PER_FRAME - execution_time;
	wolf->frametime = execution_time / 1000.0;
	if (remaining_time > 0)
		SDL_Delay(remaining_time);
}

void		wolf3d_close(t_wolf3d *wolf)
{
	wolf3d_audio_release(wolf);
	if (wolf->map)
		wolf3d_map_destroy(wolf->map);
	if (wolf)
		wolf3d_destroy_graphics(wolf);
	free(wolf);
	wolf = NULL;
	SDL_Quit();
}

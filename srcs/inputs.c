/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 03:37:15 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/25 04:01:46 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D/wolf3d.h"

static void	wolf3d_key_up(const unsigned char *keystate, t_wolf3d *wolf)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (keystate[SDL_SCANCODE_UP])
	{
		x = (int)(wolf->player.x + wolf->player.dirx
				* wolf3d_player_get_movespeed(wolf));
		y = (int)(wolf->player.y);
		if (x && y && wolf->map->map[x][y] && wolf->map->map[x][y] == '0')
			wolf->player.x += wolf->player.dirx *
				wolf3d_player_get_movespeed(wolf);
		x = (int)(wolf->player.x);
		y = (int)(wolf->player.y + wolf->player.diry
				* wolf3d_player_get_movespeed(wolf));
		if (x && y && wolf->map->map[x][y] == '0')
			wolf->player.y += wolf->player.diry *
				wolf3d_player_get_movespeed(wolf);
	}
}

static void	wolf3d_key_down(const unsigned char *keystate, t_wolf3d *wolf)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (keystate[SDL_SCANCODE_DOWN])
	{
		x = (int)(wolf->player.x - wolf->player.dirx
				* wolf3d_player_get_movespeed(wolf));
		y = (int)(wolf->player.y);
		if (x && y && wolf->map->map[x][y] && wolf->map->map[x][y] == '0')
			wolf->player.x -= wolf->player.dirx *
				wolf3d_player_get_movespeed(wolf);
		x = (int)(wolf->player.x);
		y = (int)(wolf->player.y - wolf->player.diry
				* wolf3d_player_get_movespeed(wolf));
		if (x && y && wolf->map->map[x][y] == '0')
			wolf->player.y -= wolf->player.diry *
				wolf3d_player_get_movespeed(wolf);
	}
}

static void	wolf3d_key_left(t_wolf3d *wolf)
{
	double	olddirx;
	double	oldplanex;

	olddirx = wolf->player.dirx;
	oldplanex = wolf->raycaster.planex;
	wolf->player.dirx = wolf->player.dirx *
		cos(wolf3d_player_get_rotspeed(wolf)) - wolf->player.diry *
		sin(wolf3d_player_get_rotspeed(wolf));
	wolf->player.diry = olddirx * sin(wolf3d_player_get_rotspeed(wolf)) +
		wolf->player.diry * cos(wolf3d_player_get_rotspeed(wolf));
	wolf->raycaster.planex = wolf->raycaster.planex *
		cos(wolf3d_player_get_rotspeed(wolf)) - wolf->raycaster.planey *
		sin(wolf3d_player_get_rotspeed(wolf));
	wolf->raycaster.planey = oldplanex *
		sin(wolf3d_player_get_rotspeed(wolf)) + wolf->raycaster.planey *
		cos(wolf3d_player_get_rotspeed(wolf));
}

static void	wolf3d_key_right(t_wolf3d *wolf)
{
	double	olddirx;
	double	oldplanex;

	olddirx = wolf->player.dirx;
	oldplanex = wolf->raycaster.planex;
	wolf->player.dirx = wolf->player.dirx *
		cos(-wolf3d_player_get_rotspeed(wolf)) - wolf->player.diry *
		sin(-wolf3d_player_get_rotspeed(wolf));
	wolf->player.diry = olddirx * sin(-wolf3d_player_get_rotspeed(wolf)) +
		wolf->player.diry * cos(-wolf3d_player_get_rotspeed(wolf));
	wolf->raycaster.planex = wolf->raycaster.planex *
		cos(-wolf3d_player_get_rotspeed(wolf)) -
		wolf->raycaster.planey * sin(-wolf3d_player_get_rotspeed(wolf));
	wolf->raycaster.planey = oldplanex *
		sin(-wolf3d_player_get_rotspeed(wolf)) + wolf->raycaster.planey *
		cos(-wolf3d_player_get_rotspeed(wolf));
}

void		wolf3d_inputs(const unsigned char *keystate, t_wolf3d *wolf)
{
	if (keystate[SDL_SCANCODE_ESCAPE])
		wolf->quit = 0;
	if (keystate[SDL_SCANCODE_UP])
		wolf3d_key_up(keystate, wolf);
	if (keystate[SDL_SCANCODE_DOWN])
		wolf3d_key_down(keystate, wolf);
	if (keystate[SDL_SCANCODE_RIGHT])
		wolf3d_key_right(wolf);
	if (keystate[SDL_SCANCODE_LEFT])
		wolf3d_key_left(wolf);
	if (keystate[SDL_SCANCODE_KP_PLUS])
		wolf3d_next_map(wolf);
	wolf->player.isrunning = keystate[SDL_SCANCODE_SPACE];
}

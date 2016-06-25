/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:47:33 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/24 22:25:14 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

double		wolf3d_player_get_movespeed(t_wolf3d *wolf)
{
	double	movespeed;

	movespeed = (wolf->player.isrunning) ? MOVE_SPEED_MODIFIER * 2 :
		MOVE_SPEED_MODIFIER;
	return (wolf->frametime * movespeed);
}

double		wolf3d_player_get_rotspeed(t_wolf3d *wolf)
{
	double movespeed;

	movespeed = (wolf->player.isrunning) ? ROT_SPEED_MODIFIER * 1.5 :
		ROT_SPEED_MODIFIER;
	return (wolf->frametime * movespeed);
}

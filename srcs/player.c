/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:47:33 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/07 20:16:28 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

double		wolf3d_player_get_movespeed(t_wolf3d *wolf)
{
	return (wolf->frametime * MOVE_SPEED_MODIFIER);
}

double		wolf3d_player_get_rotspeed(t_wolf3d *wolf)
{
	return (wolf->frametime * ROT_SPEED_MODIFIER);
}

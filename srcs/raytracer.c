/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:49:17 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/17 20:07:48 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

void		wolf3d_raycaster_sidestep(t_wolf3d *wolf)
{
	if (wolf->raycaster.raydirx < 0)
	{
		wolf->raycaster.stepx = -1;
		wolf->raycaster.sidedistx = (wolf->raycaster.rayposx -
			wolf->raycaster.mapx) * wolf->raycaster.deltadistx;
	}
	else
	{
		wolf->raycaster.stepx = 1;
		wolf->raycaster.sidedistx = (wolf->raycaster.mapx + 1.0 -
				wolf->raycaster.rayposx) * wolf->raycaster.deltadistx;
	}
	if (wolf->raycaster.raydiry < 0)
	{
		wolf->raycaster.stepy = -1;
		wolf->raycaster.sidedisty = (wolf->raycaster.rayposy -
				wolf->raycaster.mapy) * wolf->raycaster.deltadisty;
	}
	else
	{
		wolf->raycaster.stepy = 1;
		wolf->raycaster.sidedisty = (wolf->raycaster.mapy + 1.0 -
				wolf->raycaster.rayposy) * wolf->raycaster.deltadisty;
	}
}

void		wolf3d_raycaster_rayhit(t_wolf3d *wolf)
{
	while (wolf->raycaster.hit == 0)
	{
		if (wolf->raycaster.sidedistx < wolf->raycaster.sidedisty)
		{
			wolf->raycaster.sidedistx += wolf->raycaster.deltadistx;
			wolf->raycaster.mapx += wolf->raycaster.stepx;
			wolf->raycaster.side = 0;
		}
		else
		{
			wolf->raycaster.sidedisty += wolf->raycaster.deltadisty;
			wolf->raycaster.mapy += wolf->raycaster.stepy;
			wolf->raycaster.side = 1;
		}
		if ((int)(wolf->map->map[wolf->raycaster.mapx]
			[wolf->raycaster.mapy] - 48) > 0)
			wolf->raycaster.hit = 1;
	}
}

void		wolf3d_raycaster_dda(t_wolf3d *wolf)
{
	wolf->raycaster.perpwalldist = (wolf->raycaster.side == 0) ?
		((wolf->raycaster.mapx - wolf->raycaster.rayposx + (1 -
			wolf->raycaster.stepx) / 2) / wolf->raycaster.raydirx) :
		((wolf->raycaster.mapy - wolf->raycaster.rayposy + (1 -
			wolf->raycaster.stepy) / 2) / wolf->raycaster.raydiry);
	wolf->raycaster.lineheight = (int)(WINDW_H / wolf->raycaster.perpwalldist);
	wolf->raycaster.drawstart = -(wolf->raycaster.lineheight) / 2 + WINDW_H / 2;
	if (wolf->raycaster.drawstart < 0)
		wolf->raycaster.drawstart = 0;
	wolf->raycaster.drawend = wolf->raycaster.lineheight / 2 + WINDW_H / 2;
	if (wolf->raycaster.drawend >= WINDW_H)
		wolf->raycaster.drawend = WINDW_H - 1;
}

static void	wolf3d_raycaster_position(t_wolf3d *wolf, int x)
{
	wolf->raycaster.camerax = 2 * x / (double)(WINDW_W) - 1;
	wolf->raycaster.rayposx = wolf->player.x;
	wolf->raycaster.rayposy = wolf->player.y;
	wolf->raycaster.raydirx = wolf->player.dirx
		+ wolf->raycaster.planex * wolf->raycaster.camerax;
	wolf->raycaster.raydiry = wolf->player.diry
		+ wolf->raycaster.planey * wolf->raycaster.camerax;
	wolf->raycaster.mapx = (int)(wolf->raycaster.rayposx);
	wolf->raycaster.mapy = (int)(wolf->raycaster.rayposy);
	wolf->raycaster.deltadistx = sqrt(1 + (wolf->raycaster.raydiry *
		wolf->raycaster.raydiry) / (wolf->raycaster.raydirx *
			wolf->raycaster.raydirx));
	wolf->raycaster.deltadisty = sqrt(1 + (wolf->raycaster.raydirx *
		wolf->raycaster.raydirx) / (wolf->raycaster.raydiry *
			wolf->raycaster.raydiry));
}

void		wolf3d_raycaster(t_wolf3d *wolf)
{
	int		x;

	x = -1;
	while (++x < WINDW_W)
	{
		wolf->raycaster.hit = 0;
		wolf3d_raycaster_position(wolf, x);
		wolf3d_raycaster_sidestep(wolf);
		wolf3d_raycaster_rayhit(wolf);
		wolf3d_raycaster_dda(wolf);
		wolf3d_draw_raycaster(wolf, x);
	}
}

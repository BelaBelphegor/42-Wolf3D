/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:04:46 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/18 20:11:47 by tiboitel         ###   ########.fr       */
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
	char			quit;
	SDL_Event		e;
	unsigned int	execution_time;
	unsigned int	remaining_time;
	unsigned int	current_time;

	quit = 1;
	while (quit)
	{
		current_time = SDL_GetTicks();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 0;
			if (e.type == SDL_KEYDOWN)
				quit = 0;
		}
		//Game initilisation
		wolf->player.x = 3;
		wolf->player.y = 3;
		// Initial direction vector
		wolf->player.dirx = -1;
		wolf->player.diry = 0;
		// 2D raycaster camera plane
		wolf->raycaster.planex = 0;
		wolf->raycaster.planey = 0.66;
		// Calculate x-coordinate on the camera plane.
		int		x;

		x = 0;
		SDL_SetRenderDrawColor(wolf->renderer, 0, 0, 0, 0);
		SDL_RenderClear(wolf->renderer);
		SDL_RenderPresent(wolf->renderer);
		while (x < WINDW_W)
		{
			wolf->raycaster.camerax = 2 * x / (double)WINDW_W - 1;
			wolf->raycaster.rayposx = wolf->player.x;
			wolf->raycaster.rayposy = wolf->player.y;
			wolf->raycaster.raydirx = wolf->player.dirx
				+ wolf->raycaster.planex * wolf->raycaster.camerax;
			wolf->raycaster.raydiry = wolf->player.diry
				+ wolf->raycaster.planey * wolf->raycaster.camerax;
		// Which box of the map we're in.
		wolf->raycaster.mapx = (int)(wolf->raycaster.rayposx);
		wolf->raycaster.mapy = (int)(wolf->raycaster.rayposy);
		//length of rat form one x or y-side to next x or y-side;
		wolf->raycaster.deltadistx = ft_sqrt(1 + (wolf->raycaster.raydiry *
			wolf->raycaster.deltadisty) / (wolf->raycaster.raydirx *
				wolf->raycaster.deltadistx));
		wolf->raycaster.deltadisty = ft_sqrt(1 + (wolf->raycaster.raydirx *
			wolf->raycaster.deltadistx) / (wolf->raycaster.raydiry *
				wolf->raycaster.deltadisty));
		//What direction to step in x or y-direction (+1 ou -1)
		// hit = is wall hit ?
		// side = Est/West or North/South
		// Calculate step and initial sidedistance
		if (wolf->raycaster.raydirx < 0)
		{
			wolf->raycaster.stepx = -1;
			wolf->raycaster.sidedistx = (wolf->raycaster.rayposx - wolf->raycaster.mapx) * 
				wolf->raycaster.deltadistx;
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
			wolf->raycaster.sidedisty = (wolf->raycaster.rayposy - wolf->raycaster.mapy) * 
				wolf->raycaster.deltadisty;
		}
		else
		{
			wolf->raycaster.stepy = 1;
			wolf->raycaster.sidedisty = (wolf->raycaster.mapy + 1.0 -
				wolf->raycaster.rayposy) * wolf->raycaster.deltadisty;
		}

		// Start of Digital Differential Analyse algorithm
		while (wolf->raycaster.hit == 0)
		{
			// Jump to next square in X-Direction or Y-Direction
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
			// Chceck if ray has hit wall
			if (wolf->map->map[wolf->raycaster.mapx][wolf->raycaster.mapy] > 0)
				wolf->raycaster.hit = 1;
		}
		wolf->raycaster.perpwalldist = (wolf->raycaster.side == 0) ?
			((wolf->raycaster.mapx - wolf->raycaster.rayposx + (1 -
				wolf->raycaster.stepx) / 2) / wolf->raycaster.raydirx):
			((wolf->raycaster.mapy - wolf->raycaster.rayposy + (1 -
				wolf->raycaster.stepy) / 2) / wolf->raycaster.raydiry);
		//Calculate height of line draw on screen.
		wolf->raycaster.lineheight = (int)WINDW_H / wolf->raycaster.perpwalldist;	
		// calculate lowest and highest pixel to fill in current stripe
		wolf->raycaster.drawstart = -(wolf->raycaster.lineheight) / 2 + WINDW_H / 2;
		if (wolf->raycaster.drawstart < 0)
			wolf->raycaster.drawstart = 0;
		wolf->raycaster.drawend = wolf->raycaster.lineheight / 2 + WINDW_H / 2;	
		if (wolf->raycaster.drawend >= WINDW_H)
			wolf->raycaster.drawend = WINDW_H - 1;

		ft_putnbr(wolf->raycaster.drawstart);
		ft_putchar('e');
		ft_putnbr(wolf->raycaster.drawend);
		ft_putchar('\n');
		int i = wolf->raycaster.drawstart;
		while (i < wolf->raycaster.drawend)
		{
			SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 0);
			SDL_RenderDrawPoint(wolf->renderer, x, i);
			SDL_RenderPresent(wolf->renderer);
			i++;
		}
			x++;
		}
		wolf->frame = 0;
		// FPS.
		execution_time = SDL_GetTicks() - current_time;
		remaining_time = ((int)(SCREEN_TICKS_PER_FRAME - execution_time)
				< 0) ? 0 : SCREEN_TICKS_PER_FRAME - execution_time;
		if (remaining_time > 0)
			SDL_Delay(remaining_time);
	}
}

void		wolf3d_close(t_wolf3d *wolf)
{
	if (wolf->map)
		wolf3d_map_destroy(wolf->map);
	if (wolf)
		wolf3d_destroy_graphics(wolf);
	free(wolf);
	wolf = NULL;
	SDL_Quit();
}

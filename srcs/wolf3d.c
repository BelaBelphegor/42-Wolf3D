/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:04:46 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/17 19:28:19 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

t_wolf3d 	*wolf3d_create()
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

void	wolf3d_core(t_wolf3d *wolf)
{
	char			quit;
	SDL_Event 		e;
	unsigned int	executionTime;
	unsigned int	remainingTime;
	unsigned int	currentTime;

	quit = 1;
	while (quit)
	{
		currentTime = SDL_GetTicks();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 0;
			if (e.type == SDL_KEYDOWN)
				quit = 0;
		}
		/* Game initilisation
		wolf->player.x = 22;
		wolf->player.y = 12;
		
		// Initial direction vector
		wolf->player.dirx = -1;
		wolf->player.diry = 0;

		// 2D raycaster camera plane
		wolf->raycaster.planex = 0;
		wolf->raycaster.planey = 0.66;
		*/
		// Render
		SDL_SetRenderDrawColor(wolf->renderer, 0, 0,0, 0);
		SDL_RenderClear(wolf->renderer);
		SDL_RenderPresent(wolf->renderer);
		/*
		 * Draw one red pixel.
		 */
		SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
		SDL_RenderDrawPoint(wolf->renderer, 50, 50);
		SDL_RenderPresent(wolf->renderer);
		wolf->frame = 0;
		
		// FPS.
		executionTime = SDL_GetTicks() - currentTime;
		remainingTime = ((int)(SCREEN_TICKS_PER_FRAME - executionTime) < 0) ? 0 : SCREEN_TICKS_PER_FRAME - executionTime;
		if (remainingTime > 0)
			SDL_Delay(remainingTime);
	}
}

void	wolf3d_close(t_wolf3d *wolf)
{
	if (wolf->map)
		wolf3d_map_destroy(wolf->map);
	if (wolf)
		wolf3d_destroy_graphics(wolf);	
	free(wolf);
	wolf = NULL;
	SDL_Quit();
	exit(0);
}

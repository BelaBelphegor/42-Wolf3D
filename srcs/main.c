/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 05:19:31 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/16 20:15:52 by tiboitel         ###   ########.fr       */
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
	return (wolf);
}

int		wolf3d_init_graphics(t_wolf3d *wolf)
{
	if (SDL_Init(SDL_INIT_VIDEO != 0))
	{
		dprintf(2, "Echec de l'initialisation de la SDL (%s0\n", SDL_GetError());
		return (-1);
	}
	wolf->pWindow = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDW_W, WINDW_H, SDL_WINDOW_SHOWN);
	wolf->renderer = SDL_CreateRenderer(wolf->pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (wolf->renderer == NULL)
	{
		dprintf(2, "Echec de l'initialisation du renderer (%s)\n", SDL_GetError());
		return (-1);
	}
	SDL_SetRenderDrawColor(wolf->renderer, 0, 0, 0, 0);
	SDL_RenderClear(wolf->renderer);
	SDL_RenderPresent(wolf->renderer);
	return (1);
}

void	wolf3d_close(t_wolf3d *wolf)
{
	if (wolf && wolf->pWindow)
		SDL_DestroyWindow(wolf->pWindow);
	if (wolf && wolf->renderer)
		SDL_DestroyRenderer(wolf->renderer);
	wolf3d_map_destroy(wolf->map);
	wolf->pWindow = NULL;
	wolf->renderer = NULL;
	free(wolf);
	wolf = NULL;
	SDL_Quit();	
}

void	wolf3d_core(t_wolf3d *wolf)
{
	char			quit;
	SDL_Event 		e;
	char			buffer[1024];
	unsigned int	executionTime;
	unsigned int	remainingTime;
	unsigned int	currentTime;

	quit = 1;
	readfile("maps/intro.m3d", buffer);
	ft_bzero(buffer, 1024);
	// wolf3d_init_map(wolf->map, buffer);
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
		executionTime = SDL_GetTicks() - currentTime;
		remainingTime = ((int)(SCREEN_TICKS_PER_FRAME - executionTime) < 0) ? 0 : SCREEN_TICKS_PER_FRAME - executionTime;
		if (remainingTime > 0)
			SDL_Delay(remainingTime);
	}
	return ;
}

int main(void)
{
	t_wolf3d		*wolf;
	if (!(wolf = wolf3d_create()))
	{
		wolf3d_close(wolf);
		return (-1);
	}
	if (!(wolf3d_init_graphics(wolf)))
	{
		wolf3d_close(wolf);
		return (-1);
	}
	wolf3d_core(wolf);
	wolf3d_close(wolf);
	return (0);
}

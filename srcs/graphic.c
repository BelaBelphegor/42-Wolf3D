/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:05:36 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/17 19:26:08 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

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

void	wolf3d_destroy_graphics(t_wolf3d *wolf)
{
	if (wolf && wolf->renderer)
		SDL_DestroyRenderer(wolf->renderer);
	if (wolf && wolf->pWindow)
		SDL_DestroyWindow(wolf->pWindow);
	wolf->pWindow = NULL;
	wolf->renderer = NULL;
}

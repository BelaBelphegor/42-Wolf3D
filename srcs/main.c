/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 05:19:31 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/12 18:44:59 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL/SDL.h>
#include <stdio.h>

int main(void)
{
	SDL_Window		*pWindow;
	SDL_Renderer	*renderer;	
	SDL_Event 		e;
	char			quit;

	quit = 1;
	pWindow = NULL;
	renderer = NULL;
	if (SDL_Init(SDL_INIT_VIDEO != 0))
	{
		dprintf(2, "Echec de l'initialisation de la SDL (%s0\n", SDL_GetError());
		return (-1);
	}
	pWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		dprintf(2, "Echec de l'initialisation du renderer (%s)\n", SDL_GetError());
		return (-1);
	}
	while (quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 0;
			if (e.type == SDL_KEYDOWN)
				quit = 0;
		}
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
	return (0);
}

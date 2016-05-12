/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 05:19:31 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/12 18:00:39 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL/SDL.h>
#include <stdio.h>

int main(void)
{
	SDL_Window	*pWindow;
	
	pWindow = NULL;
	if (SDL_Init(SDL_INIT_VIDEO != 0))
	{
		fprintf(stdout, "Echec de l'initialisation de la SDL (%s0\n", SDL_GetError());
		return (-1);
	}
	pWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (pWindow)
	{
		SDL_Delay(3000);
		SDL_DestroyWindow(pWindow);
	}
	SDL_Quit();
	return (0);
}

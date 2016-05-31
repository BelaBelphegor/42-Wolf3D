/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:05:36 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/31 21:56:46 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

int		wolf3d_init_graphics(t_wolf3d *wolf)
{
	unsigned int pixels[WINDW_H * WINDW_W];

	if (SDL_Init(SDL_INIT_VIDEO != 0))
	{
		ft_putstr_fd(SDL_GetError(), 2);
		return (-1);
	}
	wolf->pWindow = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WINDW_W, WINDW_H, SDL_WINDOW_SHOWN);
	wolf->renderer = SDL_CreateRenderer(wolf->pWindow, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (wolf->renderer == NULL)
	{
		ft_putstr_fd(SDL_GetError(), 2);
		return (-1);
	}
	wolf->texture =	SDL_CreateTexture(wolf->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDW_W, WINDW_H);
	memset(pixels, 0x00FFFFFF, WINDW_H * WINDW_W * sizeof(unsigned int));
	SDL_UpdateTexture(wolf->texture, NULL, pixels, WINDW_H * sizeof(unsigned int));
	SDL_SetRenderDrawColor(wolf->renderer, 0, 0, 0, 0);
	SDL_RenderClear(wolf->renderer);
	SDL_RenderPresent(wolf->renderer);
	return (1);
}

void	wolf3d_draw_raycaster(t_wolf3d *wolf, unsigned int x)
{
	SDL_Color color[4] = {
			{108, 2, 119, 255},
			{161, 6, 132, 255},
			{114, 162, 100, 255},
			{121, 28, 248, 255}
			};
			SDL_Color tmp;
			tmp = color[(wolf->map->map[wolf->raycaster.mapx][wolf->raycaster.mapy]) - 48];
			if (wolf->raycaster.side == 1)
			{
				tmp.r = tmp.r / 2;
				tmp.b = tmp.b / 2;
				tmp.g = tmp.g / 2;
			
			}
			int pitch;
			int a = wolf->raycaster.drawstart;	
			void *upixels;
			if (SDL_LockTexture(wolf->texture, NULL, &upixels, &pitch) < 0)
				printf("SDL lock fucked up.\n");
			uint32_t *dst;
			SDL_Color *ucolor;
			while (a++ < wolf->raycaster.drawend)
			{
				dst = (uint32_t *)((uint8_t *)upixels + a * pitch);
				ucolor = &tmp;
				*(dst + x - 1) = (0xFF000000 | (ucolor->r << 16) | (ucolor->g << 8) | ucolor->b);
			}
			SDL_UnlockTexture(wolf->texture);
}

void	wolf3d_render(t_wolf3d *wolf)
{
		SDL_RenderClear(wolf->renderer);
		SDL_RenderCopy(wolf->renderer, wolf->texture, NULL, NULL);
		SDL_RenderPresent(wolf->renderer);
		wolf->frame = 0;
		// FPS.
}

void	wolf3d_destroy_graphics(t_wolf3d *wolf)
{
	if (wolf && wolf->renderer)
		SDL_DestroyRenderer(wolf->renderer);
	if (wolf && wolf->pWindow)
		SDL_DestroyWindow(wolf->pWindow);
	SDL_DestroyTexture(wolf->texture);
	wolf->pWindow = NULL;
	wolf->renderer = NULL;
}

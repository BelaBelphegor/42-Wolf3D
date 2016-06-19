/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:05:36 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/19 22:54:50 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

int			wolf3d_init_graphics(t_wolf3d *wolf)
{
	unsigned int pixels[WINDW_H * WINDW_W];

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
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
	wolf->texture = SDL_CreateTexture(wolf->renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WINDW_W, WINDW_H);
	memset(pixels, 0xFFFFFFFF, WINDW_H * WINDW_W * sizeof(unsigned int));
	SDL_UpdateTexture(wolf->texture, NULL, pixels, WINDW_H *
			sizeof(unsigned int));
	SDL_SetRenderDrawColor(wolf->renderer, 0, 0, 0, 0);
	SDL_RenderClear(wolf->renderer);
	SDL_RenderPresent(wolf->renderer);
	return (1);
}

SDL_Color	wolf3d_choose_color(t_wolf3d *wolf)
{
	SDL_Color	color[4] = {
		{108, 2, 119, 255},
		{161, 6, 132, 255},
		{114, 162, 100, 255},
		{121, 28, 248, 255}
	};
	SDL_Color	tmp;

	tmp = color[(wolf->map->map[wolf->raycaster.mapx]
		[wolf->raycaster.mapy]) - 49];
	if (wolf->raycaster.side > 0 && wolf->raycaster.raydiry > 0)
		tmp = color[0];
	else if (wolf->raycaster.side > 0 && wolf->raycaster.raydiry < 0)
		tmp = color[1];
	else if (wolf->raycaster.side == 0 && wolf->raycaster.raydirx > 0)
		tmp = color [2];
	else if (wolf->raycaster.side == 0 && wolf->raycaster.raydirx < 0)
		tmp = color [3];
	return (tmp);
}

void		wolf3d_draw_raycaster(t_wolf3d *wolf, unsigned int x)
{
	int			pitch;
	int			a;
	void		*upixels;
	uint32_t	*dst;
	SDL_Color	ucolor;

	a = wolf->raycaster.drawstart;
	if (SDL_LockTexture(wolf->texture, NULL, &upixels, &pitch) < 0)
		ft_putstr_fd(SDL_GetError(), 2);
	while (a++ < wolf->raycaster.drawend)
	{
		dst = (uint32_t *)((uint8_t *)upixels + a * pitch);
		ucolor = wolf3d_choose_color(wolf);
		*(dst + x - 1) = (0xFF000000 | (ucolor.r << 16) |
			(ucolor.g << 8) | ucolor.b);
	}
	SDL_UnlockTexture(wolf->texture);
}

void		wolf3d_render(t_wolf3d *wolf)
{
	unsigned int	pixels[WINDW_H * WINDW_W];
	SDL_Rect 		dstrec;
	SDL_Rect		srcrec;

	SDL_RenderClear(wolf->renderer);
	srcrec.x = ((wolf->mousex < WINDW_W / 2) ? ((acos(wolf->player.dirx) * 180 / 3.14)) :
			(360 - (acos(wolf->player.dirx) * 180 / 3.14))) * (WINDW_W / 360);
	if (srcrec.x < 0)
		srcrec.x = 0;
	srcrec.y = 0;
	srcrec.w = WINDW_W - (1680 % 180);
	srcrec.h = 1050;
	dstrec.x = 0;
	dstrec.y = -WINDW_H / 2 - 75;
	dstrec.h = 1050;
	dstrec.w = 1680;
	SDL_RenderCopy(wolf->renderer, wolf->skybox, &srcrec, &dstrec);	
	SDL_SetTextureBlendMode(wolf->texture, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(wolf->renderer, wolf->texture, NULL, NULL);
	SDL_RenderPresent(wolf->renderer);	
	wolf->frame = 0;
	memset(pixels, 0xFF000000, WINDW_H * WINDW_W * sizeof(unsigned int));
	SDL_UpdateTexture(wolf->texture, NULL, pixels, WINDW_H *
			sizeof(unsigned int));	
}

void		wolf3d_destroy_graphics(t_wolf3d *wolf)
{
	if (wolf && wolf->renderer)
		SDL_DestroyRenderer(wolf->renderer);
	if (wolf && wolf->pWindow)
		SDL_DestroyWindow(wolf->pWindow);
	SDL_DestroyTexture(wolf->texture);
	SDL_DestroyTexture(wolf->skybox);
	wolf->pWindow = NULL;
	wolf->renderer = NULL;
}

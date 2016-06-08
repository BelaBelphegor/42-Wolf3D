/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 19:37:34 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/08 20:18:38 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

t_wwav		*wolf_audio_handler()
{
	static t_wwav	*audio_handler;

	if (!audio_handler)
		audio_handler = (t_wwav *)ft_memalloc(sizeof(t_wwav));
	return (audio_handler);
}

void		wolf3d_audio_callback(void *userdata, unsigned char	*stream,
	int length)
{
	t_wwav		*audio_handler;

	(void)userdata;
	audio_handler = wolf_audio_handler();
	if (audio_handler->audio_len == 0)
		return ;
	length = (length > (int)audio_handler->audio_len ? audio_handler->audio_len :
		length);
	SDL_MixAudio(stream, audio_handler->wav_buffer, length, SDL_MIX_MAXVOLUME);
	audio_handler->audio_pos += length;
	audio_handler->audio_len -= length;
}

void		wolf3d_audio_init()
{
	t_wwav		*audio_handler;

	audio_handler = wolf_audio_handler();
	if (SDL_LoadWAV(MUSIC_LOOP, &(audio_handler->wav_spec),
		&(audio_handler->wav_buffer), &(audio_handler->wav_length)) == NULL)
			ft_putstr_fd(SDL_GetError(), 2);
	audio_handler->wav_spec.callback = wolf3d_audio_callback;
	audio_handler->wav_spec.userdata = NULL;
	audio_handler->audio_pos = audio_handler->wav_buffer;
	audio_handler->audio_len = audio_handler->wav_length;
	if (SDL_OpenAudio(&(audio_handler->wav_spec), NULL) < 0)
	{
		ft_putstr_fd(SDL_GetError(), 2);
		return ;
	}
	SDL_PauseAudio(0);
}

void		wolf_audio_handler_release()
{
	t_wwav		*audio_handler;

	audio_handler = wolf_audio_handler();
	SDL_CloseAudio();
	SDL_FreeWAV(audio_handler->wav_buffer);
	free(audio_handler);
	audio_handler = NULL;
}

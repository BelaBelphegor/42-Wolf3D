/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 19:37:34 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/08 19:47:26 by tiboitel         ###   ########.fr       */
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
	int lenght)
{
}

void		wolf_audio_handler_release()
{
}

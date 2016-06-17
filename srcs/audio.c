#include <Wolf3D/wolf3d.h>

int		wolf3d_audio_init(t_wolf3d *wolf)
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 8096) == -1)
		return (-1);
	wolf->music = Mix_LoadWAV(MUSIC_LOOP);
	if (wolf->music == NULL)
		return (-1);
	if (Mix_PlayChannel(-1, wolf->music, -1) == -1)
		return (-1);
	return (1);
}

void	wolf3d_audio_release(t_wolf3d *wolf)
{
	if (wolf->music == NULL)
		return ;
	Mix_FreeChunk(wolf->music);
	Mix_CloseAudio();
}

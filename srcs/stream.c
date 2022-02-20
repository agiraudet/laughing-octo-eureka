/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:26:16 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/20 20:15:18 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boids.h"
#include "data.h"

float	test_freq()
{
	t_pos	pos;
	data_pos_single(&pos, 0);
	return (pos.x + 50.);
}

int	write_stream(void *ptr)
{
	float	*fstream;
	uint64_t	smp;
	int		i;
	double	x;
	double time;
	double	freq;

	fstream = (float *)ptr;


	i = 0;
	smp = 0;
	while (1)
	{
		freq = test_freq();
		i++;
		time = (smp +i) / 44100.0;
		x = 2.0 * M_PI * time * freq;
		fstream[2 * i + 0] = 0.2 * sin(x);
		fstream[2 * i + 1] = 0.2 * sin(x);
		if (i > 32768)
		{
			smp += 32768;
			i = 0;
		}
	}
}



void	cb(void *userdata, uint8_t *stream, int len)
{
	float	*fstream;
	float	*g_stream;
	int	i = 0;
	fstream = (float *)stream;
	g_stream = (float *)userdata;

	while (i < len / 8)
	{
		i++;
		fstream[2 * i + 0] = g_stream[2 * i + 0];
		fstream[2 * i + 1] = g_stream[2 * i + 1];
	}
}
		


int	run(void *ptr)
{
	SDL_AudioSpec audio_spec_wanted;
	SDL_AudioSpec audio_spec;
	SDL_memset(&audio_spec_wanted, 0, sizeof(audio_spec_wanted));
	audio_spec_wanted.freq = 44100;
	audio_spec_wanted.format = AUDIO_F32;
	audio_spec_wanted.channels = 2;
	audio_spec_wanted.samples = 512;
	audio_spec_wanted.callback = cb;
	audio_spec_wanted.userdata = ptr;

	SDL_AudioDeviceID audio_device_id;
	audio_device_id = SDL_OpenAudioDevice(NULL, 0, &audio_spec_wanted, &audio_spec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	SDL_PauseAudioDevice(audio_device_id, 0);
	return (0);
}

int stream_start()
{
	float	fstream[140000];

	SDL_Thread	*th1;
	SDL_Thread	*th2;

	th2 = SDL_CreateThread(write_stream, "test2", (void*)&fstream);
	SDL_DetachThread(th2);

	/*
	th1 = SDL_CreateThread(run, "test1", (void*)&fstream);
	SDL_DetachThread(th1);
	*/
	run((void*)&fstream);
	return (0);

}		

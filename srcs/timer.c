/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 23:14:59 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/20 18:20:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boids.h"

void	timer_init(t_timer *tm)
{
	tm->start_time = SDL_GetTicks();
	tm->relative_time = 0;
	tm->frames = 0;
	tm->avg_fps = 0;
}

void	timer_update(t_timer *tm)
{
	tm->relative_time = SDL_GetTicks() - tm->start_time;
	tm->frames += 1;
	if (tm->frames > 200000)
		tm->frames = 0;
	tm->avg_fps = tm->frames / (tm->relative_time / 1000.);
}

void	timer_capfps(t_settings *set, t_timer *tm)
{
	int	frame_ticks;

	frame_ticks = SDL_GetTicks() - tm->start_time - tm->relative_time;
	if (frame_ticks < 1000 / set->fps_max)
		SDL_Delay(1000 / set->fps_max - frame_ticks);
	timer_update(tm);
	if (set->debug_fps)
		printf("%f\n", tm->avg_fps);
}

void	timer_capbpm(t_timer *tm, size_t bpm)
{
	int	frame_ticks;

	frame_ticks = SDL_GetTicks() - tm->start_time - tm->relative_time;
	printf("\n%d\n", frame_ticks);
	while (frame_ticks < bpm * 10 )
	{
		SDL_Delay(1);
		frame_ticks = SDL_GetTicks() - tm->start_time - tm->relative_time;
		printf(">%d\n", frame_ticks);
	}
	timer_update(tm);
}

t_timer	*timer_new(void)
{
	t_timer	*tm;

	tm = (t_timer *)malloc(sizeof(t_timer));
	if (!tm)
		return (0);
	timer_init(tm);
	return (tm);
}

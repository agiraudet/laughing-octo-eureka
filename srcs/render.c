/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 22:02:18 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/20 16:06:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boids.h"

void	render_draw_circle(t_scene *sc, t_pos *pos, double radius)
{
	double	error;
	double	x;
	double	y;
	double	cx;
	double	cy;

	error = -radius;
	x = radius - 0.5;
	y = 0.5;
	cx = pos->x - 0.5;
	cy = pos->y - 0.5;

	while (x >= y)
	{
		SDL_RenderDrawPointF(sc->ren, cx + x, cy + y);
		SDL_RenderDrawPointF(sc->ren, cx + y, cy + x);
		if (x != 0)
		{
			SDL_RenderDrawPointF(sc->ren, cx - x, cy + y);
			SDL_RenderDrawPointF(sc->ren, cx + y, cy - x);
		}
		if (y != 0)
		{
			SDL_RenderDrawPointF(sc->ren, cx + x, cy - y);
			SDL_RenderDrawPointF(sc->ren, cx - y, cy + x);
		}
		if (x != 0 && y != 0)
		{
			SDL_RenderDrawPointF(sc->ren, cx - x, cy - y);
			SDL_RenderDrawPointF(sc->ren, cx - y, cy - x);
		}
		error += y;
		y++;
		error += y;
		if (error >= 0)
		{
			x--;
			error -= x;
			error -= x;
		}
	}
}

void	render_visual_range(t_scene *sc, t_boid *boid)
{
	SDL_SetRenderDrawColor(sc->ren, 0xFF, 0xFF, 0xFF, 0xFF);
	render_draw_circle(sc, &boid->pos, sc->set->boid_visual_range);
}

void	render_one_boid(t_scene *sc, t_boid *boid)
{
	SDL_Rect	rect;

	rect.x = boid->pos.x;
	rect.y = boid->pos.y;
	rect.h = sc->set->boid_hg;
	rect.w = sc->set->boid_wd;
	SDL_SetRenderDrawColor(sc->ren, boid->color[0], boid->color[1], boid->color[2], 0x00);
	SDL_RenderFillRect(sc->ren, &rect);
	if (sc->set->debug_visual_range)
		render_visual_range(sc, boid);
}

void	render_boids(t_scene *sc, t_boid **boids)
{
	int	i;

	i = 0;
	while (boids[i])
		render_one_boid(sc, boids[i++]);
}

void	render_all(t_scene *sc, t_boid **boids)
{
	SDL_SetRenderDrawColor(sc->ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(sc->ren);
	render_boids(sc, boids);
	SDL_RenderPresent(sc->ren);
	timer_capfps(sc->set, sc->time);
}

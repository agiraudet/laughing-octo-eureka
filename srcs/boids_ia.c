/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boids_ia2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:30:48 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/19 17:49:12 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boids.h"

void	boid_keep_inside(t_settings *set, t_boid *boid)
{
	if (boid->pos.x < (double)set->margin)
		boid->dir.x += set->turn_factor;
	if (boid->pos.x + set->boid_wd > set->sc_wd - (double)set->margin)
		boid->dir.x -= set->turn_factor;
	if (boid->pos.y < (double)set->margin)
		boid->dir.y += set->turn_factor;
	if (boid->pos.y + set->boid_hg > set->sc_hg - (double)set->margin)
		boid->dir.y -= set->turn_factor;
}

void	boid_init_vectors(t_pos *a, t_pos *b, t_pos *c)
{
	a->x = 0.;
	a->y = 0.;
	b->x = 0.;
	b->y = 0.;
	c->x = 0.;
	c->y = 0.;
}

void	boid_scan(t_settings *set, t_boid **boids, int self)
{
	t_pos	center;
	t_pos	other;
	t_pos	velocity;
	double	dist;
	int		i;
	int		n;

	i = 0;
	n = 0;
	boid_init_vectors(&center, &other, &velocity);
	while (boids[i])
	{
		if (i != self)
		{
			dist = calcul_dist(&boids[i]->pos, &boids[self]->pos);
			if (dist < set->boid_visual_range)
			{
				center.x += boids[i]->pos.x;
				center.y += boids[i]->pos.y;
				velocity.x += boids[i]->dir.x;
				velocity.y += boids[i]->dir.y;
				n++;
			}
			if (dist < set->min_dist)
			{
				other.x += boids[self]->pos.x - boids[i]->pos.x;
				other.y += boids[self]->pos.y - boids[i]->pos.y;
			}
		}
		i++;
	}
	if (n)
	{
		center.x /= (double)n;
		center.y /= (double)n;
		boids[self]->dir.x += (center.x - boids[self]->pos.x) * set->centering_factor;
		boids[self]->dir.y += (center.y - boids[self]->pos.y) * set->centering_factor;
	}
	boids[self]->dir.x += other.x * set->avoid_factor;
	boids[self]->dir.y += other.y * set->avoid_factor;
	if (n)
	{
		velocity.x /= (double)n;
		velocity.y /= (double)n;
		boids[self]->dir.x += (velocity.x - boids[self]->dir.x) * set->matching_factor;
		boids[self]->dir.y += (velocity.y - boids[self]->dir.y) * set->matching_factor;
	}
}

void	boid_limit_speed(t_settings *set, t_boid *boid)
{
	double	speed;

	speed = sqrt(boid->dir.x * boid->dir.x + boid->dir.y * boid->dir.y);
	if (speed > set->speed_limit)
	{
		boid->dir.x = (boid->dir.x / speed) * set->speed_limit;
		boid->dir.y = (boid->dir.y / speed) * set->speed_limit;
	}
}

void	boid_move(t_boid *boid)
{
	boid->pos.x += boid->dir.x;
	boid->pos.y += boid->dir.y;
}

void	boid_update(t_scene *sc, t_boid **boids)
{
	int	i;

	i = 0;
	while (boids[i])
	{
		boid_scan(sc->set, boids, i);
		boid_limit_speed(sc->set, boids[i]);
		boid_keep_inside(sc->set, boids[i]);
		boid_move(boids[i]);
		i++;
	}
}

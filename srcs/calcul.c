/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 23:48:48 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/19 15:36:52 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boids.h"

double	calcul_dist(t_pos *pos_a, t_pos *pos_b)
{
	return (sqrt(pow((pos_b->x - pos_a->x), 2) + pow((pos_b->y -pos_a->y), 2)));
}

int	calcul_rand(int min, int max)
{
	return ((rand() + min) % (max + 1 - min));
}

double	calcul_randf(double min, double max)
{
	double	range;
	double	div;

	range = (max - min);
	div = RAND_MAX / range;
	return (min + (rand() / div));
}

void	calcul_randseed(void)
{
	time_t	t;
	srand((unsigned) time(&t));
}

void	calcul_randpos(t_pos *pos, int xmin, int xmax, int ymin, int ymax)
{
	pos->x = calcul_rand(xmin, xmax);
	pos->y = calcul_rand(ymin, ymax);
}

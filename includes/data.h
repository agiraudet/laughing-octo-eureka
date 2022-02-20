/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:43:43 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/20 16:35:21 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

void    data_init(t_scene *sc, t_boid **boids);
void    data_screen_size(t_pos *size);
int     data_nb_boids(void);
void    data_pos_average(t_pos *average);
void    data_pos_single(t_pos *single, int id);
void    data_boids_sector(int nb_sector_x, int nb_sector_y, int id, t_pos *pos);
void    data_set_color(int id, Uint8 r, Uint8 g, Uint8 b);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:51:13 by ufalzone          #+#    #+#             */
/*   Updated: 2025/02/24 18:36:23 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define MAX_PHILO 200

#include "global.h"

typedef struct s_philo
{
	int id;
	long dernier_repas;
	int nb_repas;
	pthread_mutex_t *fourchette_gauche;
	pthread_mutex_t *fourchette_droite;
	long temps_mort;
	t_global *global;
}	t_philo;

long	ft_atoi(const char *str);
size_t	ft_strlen(const char *s);

#endif

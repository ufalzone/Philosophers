/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:51:13 by ufalzone          #+#    #+#             */
/*   Updated: 2025/02/25 15:39:27 by ufalzone         ###   ########.fr       */
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

//COLOR
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

typedef struct s_philo
{
	int id;
	pthread_t id_thread;
	long dernier_repas;
	int nb_repas;
	pthread_mutex_t *fourchette_gauche;
	pthread_mutex_t *fourchette_droite;
	long temps_mort;
	t_global *global;
}	t_philo;

// Utils Libft
long	ft_atoi(const char *str);
size_t	ft_strlen(const char *s);

// Utils Philo
void	check_args(int ac, char **av);

// Init
void	init_global(t_global *global, int ac, char **av);
void	init_fourchette(t_global *global);
void	init_all_philo(t_global *global);

// Exec
void	exec_philo(t_global *global);


#endif

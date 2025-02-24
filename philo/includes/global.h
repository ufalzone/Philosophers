/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:34:18 by ufalzone          #+#    #+#             */
/*   Updated: 2025/02/24 19:04:49 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
#define GLOBAL_H

struct s_philo;

typedef struct s_global
{
	int id;
	int nb_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_eat;
	int if_nb_eat;
	pthread_mutex_t *fourchette;
	struct s_philo **philo_array;
}	t_global;

typedef struct s_thread_data
{
	struct s_philo *philo;
	t_global *global;
} t_thread_data;

#endif

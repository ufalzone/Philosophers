/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:34:18 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/03 18:44:01 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <pthread.h>

struct	s_philo;
struct	s_thread_data;

typedef struct s_global
{
	int						nb_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nb_eat;
	int						if_nb_eat;
	int						somebody_is_dead;
	pthread_mutex_t			mutex_death;
	pthread_mutex_t			mutex_print;
	pthread_mutex_t			mutex_meal;
	pthread_mutex_t			*fourchette;
	struct s_philo			**philo_array;
	struct timeval			start_time;
	pthread_t				monitor_thread;
	struct s_thread_data	**thread_data;
}							t_global;

typedef struct s_thread_data
{
	struct s_philo			*philo;
	t_global				*global;
}							t_thread_data;

#endif

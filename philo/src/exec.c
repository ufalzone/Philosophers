/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:12 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/03 18:23:37 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void create_philo_thread(t_global *global)
{
	int i;

	i= 0;
	while (i < global->nb_philo)
	{
		global->thread_data[i] = malloc(sizeof(t_thread_data));
		if (!global->thread_data[i])
			return;
		global->thread_data[i]->philo = global->philo_array[i];
		global->thread_data[i]->global = global;
		global->philo_array[i]->dernier_repas = elapsed_time(global->start_time);
		global->philo_array[i]->nb_repas = 0;
		pthread_create(&global->philo_array[i]->id_thread, NULL, (void *)routine, global->thread_data[i]);
		usleep(100);
		i++;
	}
}

static void wait_philo_thread(t_global *global)
{
	int i;

	i = -1;
	while (++i < global->nb_philo)
		pthread_join(global->philo_array[i]->id_thread, NULL);
	pthread_join(global->monitor_thread, NULL);
	
}

static void init_exec_philo(t_global *global)
{
	gettimeofday(&global->start_time, NULL);
	pthread_mutex_init(&global->mutex_death, NULL);
	pthread_mutex_init(&global->mutex_print, NULL);
	pthread_mutex_init(&global->mutex_meal, NULL);
	global->somebody_is_dead = 0;
	global->thread_data = malloc(sizeof(t_thread_data *) * global->nb_philo);
	if (!global->thread_data)
		return;
}

void	exec_philo(t_global *global)
{
	init_exec_philo(global);
	create_philo_thread(global);
	pthread_create(&global->monitor_thread, NULL, (void *)monitor_thread, global);
	wait_philo_thread(global);
}

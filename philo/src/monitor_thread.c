/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:59:14 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/04 16:01:52 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	monitor_verif_death(t_global *global)
{
	int		i;
	long	current_time;
	long	last_meal;

	i = 0;
	while (i < global->nb_philo)
	{
		pthread_mutex_lock(&global->mutex_meal);
		current_time = elapsed_time(global->start_time);
		last_meal = global->philo_array[i]->dernier_repas;
		if (current_time - last_meal > global->time_to_die)
		{
			pthread_mutex_lock(&global->mutex_death);
			if (global->somebody_is_dead)
			{
				pthread_mutex_unlock(&global->mutex_death);
				pthread_mutex_unlock(&global->mutex_meal);
				return (1);
			}
			global->somebody_is_dead = 1;
			pthread_mutex_unlock(&global->mutex_death);
			pthread_mutex_lock(&global->mutex_print);
			printf("\033[31m[%ld] %d est mort\033[0m\n",
				current_time, global->philo_array[i]->id + 1);
			pthread_mutex_unlock(&global->mutex_print);
			pthread_mutex_unlock(&global->mutex_meal);
			return (1);
		}
		pthread_mutex_unlock(&global->mutex_meal);
		i++;
	}
	return (0);
}

static int	monitor_verif_alleat(t_global *global)
{
	int	i;

	if (global->if_nb_eat != 1)
		return (0);
	i = 0;
	while (i < global->nb_philo)
	{
		pthread_mutex_lock(&global->mutex_meal);
		if (global->philo_array[i]->nb_repas < global->nb_eat)
		{
			pthread_mutex_unlock(&global->mutex_meal);
			return (0);
		}
		pthread_mutex_unlock(&global->mutex_meal);
		i++;
	}
	pthread_mutex_lock(&global->mutex_death);
	global->somebody_is_dead = 1;
	pthread_mutex_unlock(&global->mutex_death);
	return (1);
}

void	monitor_thread(void *arg)
{
	t_global	*global;
	int			monitor_verif;
	int			monitor_is_alleat;

	global = (t_global *)arg;
	while (1)
	{
		pthread_mutex_lock(&global->mutex_death);
		if (global->somebody_is_dead != 1)
		{
			pthread_mutex_unlock(&global->mutex_death);
			monitor_verif = monitor_verif_death(global);
			monitor_is_alleat = monitor_verif_alleat(global);
			if (monitor_verif == 1 || monitor_is_alleat == 1)
				return ;
			usleep(50);
		}
		else
		{
			pthread_mutex_unlock(&global->mutex_death);
			return ;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:43:45 by ufalzone          #+#    #+#             */
/*   Updated: 2025/02/28 14:44:24 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_death(t_thread_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->global->mutex_death);
	dead = (data->global->somebody_is_dead == 1);
	pthread_mutex_unlock(&data->global->mutex_death);
	return (dead);
}

static void	print_action(t_thread_data *data, char *action)
{
	pthread_mutex_lock(&data->global->mutex_print);
	if (check_death(data))
	{
		pthread_mutex_unlock(&data->global->mutex_print);
		return ;
	}
	printf("[%ld] %d %s\n", elapsed_time(data->global->start_time),
		data->philo->id + 1, action);
	pthread_mutex_unlock(&data->global->mutex_print);
}

static void	release_forks(t_thread_data *data)
{
	pthread_mutex_unlock(data->philo->fourchette_droite);
	pthread_mutex_unlock(data->philo->fourchette_gauche);
}

static void	take_forks(t_thread_data *data)
{
	if (data->philo->id % 2 == 0)
	{
		pthread_mutex_lock(data->philo->fourchette_droite);
		print_action(data, "a prit la fourchette droite.");
		pthread_mutex_lock(data->philo->fourchette_gauche);
		print_action(data, "a prit la fourchette gauche.");
	}
	else
	{
		pthread_mutex_lock(data->philo->fourchette_gauche);
		print_action(data, "a prit la fourchette gauche.");
		pthread_mutex_lock(data->philo->fourchette_droite);
		print_action(data, "a prit la fourchette droite.");
	}
}

void	routine(void *arg)
{
	t_thread_data	*data;

	data = (t_thread_data *)arg;
	while (!check_death(data))
	{
		take_forks(data);
		pthread_mutex_lock(&data->global->mutex_meal);
		data->philo->dernier_repas = elapsed_time(data->global->start_time);
		data->philo->nb_repas++;
		pthread_mutex_unlock(&data->global->mutex_meal);
		print_action(data, "est en train de manger.");
		usleep(data->global->time_to_eat * 1000);
		if (check_death(data))
		{
			release_forks(data);
			return ;
		}
		release_forks(data);
		print_action(data, "est en train de dormir.");
		usleep(data->global->time_to_sleep * 1000);
		if (check_death(data))
			return ;
		print_action(data, "est en train de penser.");
		usleep(50);
	}
}

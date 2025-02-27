/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:12:36 by ufalzone          #+#    #+#             */
/*   Updated: 2025/02/28 00:14:42 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_thread_data *data, char *status)
{
	pthread_mutex_lock(&data->global->mutex_print);
	printf("[%ld] %d %s\n", elapsed_time(data->global->start_time) / 1000,
		data->philo->id, status);
	pthread_mutex_unlock(&data->global->mutex_print);
}

int	check_death_and_sleep(t_thread_data *data, int sleep_time)
{
	pthread_mutex_lock(&data->global->mutex_death);
	if (data->global->somebody_is_dead == 1)
	{
		pthread_mutex_unlock(&data->global->mutex_death);
		return (0);
	}
	pthread_mutex_unlock(&data->global->mutex_death);
	usleep(sleep_time);
	return (1);
}
void	release_forks(t_thread_data *data)
{
	pthread_mutex_unlock(data->philo->fourchette_droite);
	pthread_mutex_unlock(data->philo->fourchette_gauche);
}

int	philo_eat(t_thread_data *data)
{
	pthread_mutex_lock(&data->global->mutex_meal);
	data->philo->dernier_repas = elapsed_time(data->global->start_time) / 1000;
	pthread_mutex_unlock(&data->global->mutex_meal);
	print_status(data, "est en train de manger");
	if (!check_death_and_sleep(data, data->global->time_to_eat))
	{
		release_forks(data);
		return (0);
	}
	release_forks(data);
	return (1);
}

int	philo_sleep(t_thread_data *data)
{
	print_status(data, "est en train de dormir");
	if (!check_death_and_sleep(data, data->global->time_to_sleep))
		return (0);
	return (1);
}

int	philo_think(t_thread_data *data)
{
	print_status(data, "est en train de penser");
	if (!check_death_and_sleep(data, 50))
		return (0);
	return (1);
}

void	take_forks_even(t_thread_data *data)
{
	pthread_mutex_lock(data->philo->fourchette_droite);
	print_status(data, "a prit la fourchette droite");
	pthread_mutex_lock(data->philo->fourchette_gauche);
	print_status(data, "a prit la fourchette gauche");
}

void	take_forks_odd(t_thread_data *data)
{
	pthread_mutex_lock(data->philo->fourchette_gauche);
	print_status(data, "a prit la fourchette gauche");
	pthread_mutex_lock(data->philo->fourchette_droite);
	print_status(data, "a prit la fourchette droite");
}

int	take_forks(t_thread_data *data)
{
	pthread_mutex_lock(&data->global->mutex_death);
	if (data->global->somebody_is_dead == 1)
	{
		pthread_mutex_unlock(&data->global->mutex_death);
		return (0);
	}
	pthread_mutex_unlock(&data->global->mutex_death);
	if (data->philo->id % 2 == 0)
		take_forks_even(data);
	else
		take_forks_odd(data);
	return (1);
}

void	routine(void *arg)
{
	t_thread_data	*data;

	data = (t_thread_data *)arg;
	while (1)
	{
		if (!take_forks(data))
			break ;
		if (!philo_eat(data))
			break ;
		if (!philo_sleep(data))
			break ;
		if (!philo_think(data))
			break ;
	}
}

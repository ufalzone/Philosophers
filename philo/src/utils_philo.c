/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:29:24 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/05 12:44:29 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_thread_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->global->mutex_death);
	dead = (data->global->somebody_is_dead == 1);
	pthread_mutex_unlock(&data->global->mutex_death);
	return (dead);
}

long	elapsed_time(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec - start.tv_usec)
		/ 1000);
}

void	print_action(t_thread_data *data, char *action)
{
	pthread_mutex_lock(&data->global->mutex_print);
	if (check_death(data))
	{
		pthread_mutex_unlock(&data->global->mutex_print);
		return ;
	}
	printf("%ld %d %s\n",
		elapsed_time(data->global->start_time),
		data->philo->id + 1,
		action);
	pthread_mutex_unlock(&data->global->mutex_print);
}

int	get_int(t_thread_data *data)
{
	int	value;

	pthread_mutex_lock(&data->global->mutex_start);
	value = data->global->simulation_ready_to_go;
	pthread_mutex_unlock(&data->global->mutex_start);
	return (value);
}

void	wait_all_threads(t_thread_data *data)
{
	while (get_int(data) != 1)
		;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:12 by ufalzone          #+#    #+#             */
/*   Updated: 2025/02/27 22:18:35 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <sys/time.h>

long elapsed_time(struct timeval start)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec - start.tv_usec) / 1000);
}

void	routine(void *arg)
{
	t_thread_data *data;

	data = (t_thread_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->global->mutex_death);
		if (data->global->somebody_is_dead != 1)
		{
			pthread_mutex_unlock(&data->global->mutex_death);
			if (data->philo->id % 2 == 0)
			{
				pthread_mutex_lock(data->philo->fourchette_droite);
				pthread_mutex_lock(&data->global->mutex_print);
				printf("[%ld] %d a prit la fourchette droite\n",
					elapsed_time(data->global->start_time) / 1000, data->philo->id);
				pthread_mutex_unlock(&data->global->mutex_print);
				pthread_mutex_lock(data->philo->fourchette_gauche);
				pthread_mutex_lock(&data->global->mutex_print);
				printf("[%ld] %d a prit la fourchette gauche\n",
					elapsed_time(data->global->start_time) / 1000, data->philo->id);
				pthread_mutex_unlock(&data->global->mutex_print);
			}
			else
			{
				pthread_mutex_lock(data->philo->fourchette_gauche);
				pthread_mutex_lock(&data->global->mutex_print);
				printf("[%ld] %d a prit la fourchette gauche\n",
					elapsed_time(data->global->start_time) / 1000, data->philo->id);
				pthread_mutex_unlock(&data->global->mutex_print);
				pthread_mutex_lock(data->philo->fourchette_droite);
				pthread_mutex_lock(&data->global->mutex_print);
				printf("[%ld] %d a prit la fourchette droite\n",
					elapsed_time(data->global->start_time) / 1000, data->philo->id);
				pthread_mutex_unlock(&data->global->mutex_print);
			}

			// Manger
			pthread_mutex_lock(&data->global->mutex_meal);
			data->philo->dernier_repas = elapsed_time(data->global->start_time) / 1000;
			pthread_mutex_unlock(&data->global->mutex_meal);
			pthread_mutex_lock(&data->global->mutex_print);
			printf("[%ld] %d est en train de manger.\n",
				elapsed_time(data->global->start_time) / 1000, data->philo->id);
			pthread_mutex_unlock(&data->global->mutex_print);
			usleep(data->global->time_to_eat);
			pthread_mutex_lock(&data->global->mutex_death);
			if (data->global->somebody_is_dead == 1)
			{
				pthread_mutex_unlock(data->philo->fourchette_droite);
				pthread_mutex_unlock(data->philo->fourchette_gauche);
				break;
			}
			pthread_mutex_unlock(&data->global->mutex_death);
			// Relache les fourchettes
			pthread_mutex_unlock(data->philo->fourchette_droite);
			pthread_mutex_unlock(data->philo->fourchette_gauche);

			// Dormir
			pthread_mutex_lock(&data->global->mutex_print);
			printf("[%ld] %d est en train de dormir.\n",
				elapsed_time(data->global->start_time) / 1000, data->philo->id);
			pthread_mutex_unlock(&data->global->mutex_print);
			usleep(data->global->time_to_sleep);
			pthread_mutex_lock(&data->global->mutex_death);
			if (data->global->somebody_is_dead == 1)
			{
				pthread_mutex_unlock(&data->global->mutex_death);
				break;
			}
			pthread_mutex_unlock(&data->global->mutex_death);
			// Penser
			pthread_mutex_lock(&data->global->mutex_print);
			printf("[%ld] %d est en train de penser.\n",
				elapsed_time(data->global->start_time) / 1000, data->philo->id);
			pthread_mutex_unlock(&data->global->mutex_print);
			usleep(50);
		}
		else
		{
			pthread_mutex_unlock(&data->global->mutex_death);
			break;
		}
	}
}

//verif if ((elapsed_time(data->global->start_time) / 1000 - philo->dernier_repas) > (data->global->time_to_die / 1000))

int monitor_verif_death(t_global *global)
{
	int i;

	i = 0;
	while (i < global->nb_philo)
	{
		pthread_mutex_lock(&global->mutex_meal);
		if (elapsed_time(global->start_time) - global->philo_array[i]->dernier_repas > global->time_to_die)
		{
			pthread_mutex_unlock(&global->mutex_meal);
			pthread_mutex_lock(&global->mutex_death);
			global->somebody_is_dead = 1;
			pthread_mutex_unlock(&global->mutex_death);
			pthread_mutex_lock(&global->mutex_print);
			printf("\033[31m[%ld] %d est mort\033[0m\n",
			elapsed_time(global->start_time) / 1000, global->philo_array[i]->id);
			pthread_mutex_unlock(&global->mutex_print);
			return (1);
		}
			pthread_mutex_unlock(&global->mutex_meal);
			i++;
	}
	return (0);
}

void monitor_thread_2(void *arg)
{
	t_global *global;
	int i;
	int monitor_verif;

	global = (t_global *)arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&global->mutex_death);
		if (global->somebody_is_dead != 1)
		{
			pthread_mutex_unlock(&global->mutex_death);
			monitor_verif = monitor_verif_death(global);
			if (monitor_verif == 1)
			{
				printf("salut");
				return;
			}
		}
		usleep(100);
	}
}

// void monitor_thread(void *arg)
// {
// 	t_global *global;
// 	int i;

// 	global = (t_global *)arg;
// 	i = 0;
// 	pthread_mutex_lock(&global->mutex_death);
// 	while (global->somebody_is_dead != 1)
// 	{
// 		pthread_mutex_unlock(&global->mutex_death);
// 		while (i < global->nb_philo)
// 		{
// 			pthread_mutex_lock(&global->mutex_meal);
// 			if (elapsed_time(global->start_time) - global->philo_array[i]->dernier_repas > global->time_to_die)
// 			{
// 				pthread_mutex_unlock(&global->mutex_meal);
// 				pthread_mutex_lock(&global->mutex_death);
// 				global->somebody_is_dead = 1;
// 				pthread_mutex_unlock(&global->mutex_death);
// 				pthread_mutex_lock(&global->mutex_print);
// 				printf("\033[31m[%ld] %d est mort\033[0m\n",
// 					elapsed_time(global->start_time) / 1000, global->philo_array[i]->id);
// 				pthread_mutex_unlock(&global->mutex_print);
// 				return;
// 			}
// 			pthread_mutex_unlock(&global->mutex_meal);
// 			i++;
// 		}
// 		i = 0;
// 		usleep(100);
// 	}
// 	pthread_mutex_unlock(&global->mutex_death);
// }



void	exec_philo(t_global *global)
{
	int	i;
	int j;

	t_thread_data *data;

	i = 0;
	j = 0;
	gettimeofday(&global->start_time, NULL);
	pthread_mutex_init(&global->mutex_death, NULL);
	pthread_mutex_init(&global->mutex_print, NULL);
	pthread_mutex_init(&global->mutex_meal, NULL);
	global->thread_data = malloc(sizeof(t_thread_data *) * global->nb_philo);
	if (!global->thread_data)
		return;
	while (i < global->nb_philo)
	{
		global->thread_data[i] = malloc(sizeof(t_thread_data));
		if (!global->thread_data[i])
			return;
		global->thread_data[i]->philo = global->philo_array[i];
		global->thread_data[i]->global = global;
		global->philo_array[i]->dernier_repas = 0;
		pthread_create(&global->philo_array[i]->id_thread, NULL, (void *)routine, global->thread_data[i]);
		i++;
	}
	pthread_create(&global->monitor_thread, NULL, (void *)monitor_thread_2, global);
	while (j < global->nb_philo)
	{
		pthread_join(global->philo_array[j]->id_thread, NULL);
		j++;
	}
	pthread_join(global->monitor_thread, NULL);
	printf("Fin du programme\n");
}

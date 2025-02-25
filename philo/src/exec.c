/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:12 by ufalzone          #+#    #+#             */
/*   Updated: 2025/02/25 15:39:45 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	routine(void *arg)
{
	t_thread_data *data;

	data = (t_thread_data *)arg;

}

void	exec_philo(t_global *global)
{
	int	i;
	t_thread_data *data;

	i = 0;
	while (i < global->nb_philo)
	{
		data = malloc(sizeof(t_thread_data));
		if (!data)
			return;
		data->philo = global->philo_array[i];
		data->global = global;
		pthread_create(&global->philo_array[i]->id_thread, NULL, (void *)routine, data);
		i++;
	}
}

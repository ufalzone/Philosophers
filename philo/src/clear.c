/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:51:32 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/03 18:36:23 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clear_all_philo(t_global *global)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&global->mutex_death);
	pthread_mutex_destroy(&global->mutex_print);
	pthread_mutex_destroy(&global->mutex_meal);
	while (++i < global->nb_philo)
		pthread_mutex_destroy(&global->fourchette[i]);
	free(global->fourchette);
	i = -1;
	while (++i < global->nb_philo)
		free(global->philo_array[i]);
	free(global->philo_array);
	i = -1;
	while (++i < global->nb_philo)
		free(global->thread_data[i]);
	free(global->thread_data);
}

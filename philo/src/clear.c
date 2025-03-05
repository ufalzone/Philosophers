/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:51:32 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/05 12:43:23 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_error(char *message)
{
	printf("%s%s", RED, message);
	exit(1);
}

void	check_args(int ac, char **av)
{
	int		i;
	long	num;

	i = 0;
	if (ac < 5 || ac > 6)
		ft_error("Error: wrong number of arguments\n");
	while (++i < ac)
	{
		num = ft_atoi(av[i]);
		if (i == 1 && (num < 1 || num > MAX_PHILO))
			ft_error("Error: wrong number of philosophers\n");
		else if (i == 5 && (num < 0 || num > INT_MAX))
			ft_error("Error: wrong number of times to eat\n");
		else if (i != 1 && i != 5 && (num < 1 || num > INT_MAX))
			ft_error("Error: wrong number of arguments\n");
	}
}

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

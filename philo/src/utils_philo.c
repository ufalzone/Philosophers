/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:29:24 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/03 18:48:39 by ufalzone         ###   ########.fr       */
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
	printf("\033[33m[%ld]\033[0m \033[1m%d\033[0m %s\n",
		elapsed_time(data->global->start_time),
		data->philo->id + 1,
		action);
	pthread_mutex_unlock(&data->global->mutex_print);
}

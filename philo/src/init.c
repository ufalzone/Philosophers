/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:28:15 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/03 18:20:34 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_fourchette(t_global *global)
{
	int	i;
	pthread_mutex_t	*fourchette;

	i = 0;
	fourchette = malloc(sizeof(pthread_mutex_t) * global->nb_philo);
	if (!fourchette)
		return ;
	while (i < global->nb_philo)
	{
		pthread_mutex_init(&fourchette[i], NULL);
		i++;
	}
	global->fourchette = fourchette;
}

void	init_global(t_global *global, int ac, char **av)
{
	global->nb_philo = ft_atoi(av[1]);
	global->time_to_die = ft_atoi(av[2]);
	global->time_to_eat = ft_atoi(av[3]);
	global->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		global->nb_eat = ft_atoi(av[5]);
		global->if_nb_eat = 1;
	}
	else
	{
		global->nb_eat = -1;
		global->if_nb_eat = 0;
	}
}

void	init_all_philo(t_global *global)
{
	int	i;

	i = 0;
	init_fourchette(global);
	global->philo_array = malloc(sizeof(t_philo *) * global->nb_philo);
	if (!global->philo_array)
		return ;
	while (i < global->nb_philo)
	{
		global->philo_array[i] = malloc(sizeof(t_philo));
		if (!global->philo_array[i])
			return ;
		global->philo_array[i]->id = i;
		// global->philo_array[i]->id_thread = i;
		global->philo_array[i]->nb_repas = 0;
		global->philo_array[i]->fourchette_gauche = &global->fourchette[i];
		global->philo_array[i]->fourchette_droite = &global->fourchette[(i + 1) % global->nb_philo];
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:44:42 by ufalzone          #+#    #+#             */
/*   Updated: 2025/02/24 19:09:22 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//./philo nombre_de_philosophes, temps_avant_de_mourir_de_faim, temps_pour_manger, temps_pour_dormir, numbre_de_fois_qu'un_philo_doit_manger (optionnel)

#include "../includes/philo.h"


void	check_args(int ac, char **av)
{
	int		i;
	long	num;

	i = 0;
	if (ac < 5 || ac > 6)
		//message d'erreur
	while (++i < ac)
	{
		num = ft_atoi(av[i]);
		if (i == 1 && (num < 1 || num > MAX_PHILO))
			//message d'erreur
		else if (i == 5 && (num < 0 || num > INT_MAX))
			//message d'erreur
		else if (i != 1 && i != 5 && (num < 1 || num > INT_MAX))
			//message d'erreur
	}
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
void	init_fourchette(t_global *global)
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
		global->philo_array[i]->nb_repas = 0;
		global->philo_array[i]->dernier_repas = 0;
		global->philo_array[i]->fourchette_gauche = &global->fourchette[i];
		global->philo_array[i]->fourchette_droite = &global->fourchette[(i + 1) % global->nb_philo];
		i++;
	}
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
		pthread_create(&global->philo_array[i]->id, NULL, &routine, data);
		i++;
	}
}

void	routine(void *arg)
{
	t_thread_data *data;

	data = (t_thread_data *)arg;

}

int main(int ac, char **av)
{
	t_global global;

	check_args(ac, av);
	init_global(&global, ac, av);
	init_all_philo(&global);
	exec_philo(&global);
}

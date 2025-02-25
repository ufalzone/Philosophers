/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:44:42 by ufalzone          #+#    #+#             */
/*   Updated: 2025/02/25 15:52:11 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//./philo nombre_de_philosophes, temps_avant_de_mourir_de_faim, temps_pour_manger, temps_pour_dormir, numbre_de_fois_qu'un_philo_doit_manger (optionnel)

#include "../includes/philo.h"

// void	debug_print_global(t_global *global)
// {
// 	int i;

// 	printf("Nombre de philosophes: %d\n", global->nb_philo);
// 	printf("Temps avant de mourir de faim: %d\n", global->time_to_die);
// 	printf("Temps pour manger: %d\n", global->time_to_eat);
// 	printf("Temps pour dormir: %d\n", global->time_to_sleep);
// 	printf("Nombre de fois qu'un philosophe doit manger: %d\n", global->nb_eat);
// 	printf("Si nombre de repas est spécifié: %d\n", global->if_nb_eat);
// 	printf("Adresse des fourchettes: %p\n", (void *)global->fourchette);
// 	printf("Adresse du tableau des philosophes: %p\n", (void *)global->philo_array);

// 	for (i = 0; i < global->nb_philo; i++)
// 	{
// 		printf("Philosophe %d: ID_Thread: %ld, Dernier repas: %ld, Nombre de repas: %d, Adresse de la fourchette gauche: %p, Adresse de la fourchette droite: %p, Temps de mort: %ld, T_Global: %p\n",
// 			global->philo_array[i]->id
// 			// (unsigned long)global->philo_array[i]->id_thread,
// 			// global->philo_array[i]->dernier_repas,
// 			// global->philo_array[i]->nb_repas,
// 			// global->philo_array[i]->fourchette_gauche,
// 			// global->philo_array[i]->fourchette_droite,
// 			// global->philo_array[i]->temps_mort,
// 			// global->philo_array[i]->global);
// 		);
// 	}
// }

int main(int ac, char **av)
{
	t_global global;

	check_args(ac, av);
	init_global(&global, ac, av);
	init_all_philo(&global);
	exec_philo(&global);
	// debug_print_global(&global);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:44:42 by ufalzone          #+#    #+#             */
/*   Updated: 2025/03/03 18:36:47 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ./philo nombre_de_philosophes temps_avant_de_mourir_de_faim temps_pour_manger
temps_pour_dormir numbre_de_fois_qu'un_philo_doit_manger (optionnel) */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_global	global;

	check_args(ac, av);
	init_global(&global, ac, av);
	init_all_philo(&global);
	exec_philo(&global);
	clear_all_philo(&global);
	return (0);
}

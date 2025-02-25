/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:29:24 by ufalzone          #+#    #+#             */
/*   Updated: 2025/02/25 15:33:23 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void ft_error(char *message)
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

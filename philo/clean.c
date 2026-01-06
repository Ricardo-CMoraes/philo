/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:31:46 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/05 22:22:23 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->settings->n_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philo->settings->n_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(philo);
	free(forks);
}

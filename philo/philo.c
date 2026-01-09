/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:16:35 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/08 23:52:05 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_settings		settings;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (check_args(argc, argv))
		return (1);
	init_settings(&settings, argc, argv);
	forks = init_forks(&settings);
	if (!forks)
		return (write(2, "Error: Fail to allocate memory\n", 32));
	philo = init_philo(&settings, forks);
	if (!philo)
	{
		free(forks);
		return (write(2, "Error: Fail to allocate memory\n", 32));
	}
	if (!init_threads(philo))
	{
		clean_all(philo, forks);
		return (write(2, "Error: Fail thread initialization\n", 35));
	}
	monitor_routine(philo, settings.n_philos, 0);
	clean_all(philo, forks);
	return (0);
}

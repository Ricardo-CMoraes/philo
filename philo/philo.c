/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:16:35 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/07 00:17:12 by rida-cos         ###   ########.fr       */
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

// TO DO:
// TESTE DE ESTRESSE
// LEAK
// RODAR COM A FLAG
// estudar e demonstrar porque e necesspario o think delay quando e impar.

// printf("number_of_philosophers: %d\n", settings.n_philos);
// printf("time_to_die: %ld\n", settings.time_to_die);
// printf("time_to_eat: %ld\n", settings.time_to_eat);
// printf("time_to_sleep: %ld\n", settings.time_to_sleep);
// if (argc == 6)
// 	printf("[number_of_times_each_philosopher_must_eat]: %d\n", 
//			settings.times_must_eat);  

// int i = 0;
// while (i < settings.n_philos)
// {
// 	printf("\n##################\n");
// 	printf("\tid: %d\n", philo[i].id);
// 	printf("\tmeals_eaten: %d\n", philo[i].meals_eaten);
// 	printf("\tlast_meal_time: %ld\n", philo[i].last_meal_time);
// 	printf("\tfirst_fork: %p\n", philo[i].first_fork);
// 	printf("\tsecond_fork: %p\n", philo[i].second_fork);
// 	i++;
// }

// philo->settings->start_time = philo[0].last_meal_time;
// usleep(5000000);
// printf("tempo decorrido:%ld\n", get_time_ms() - philo->settings->start_time);